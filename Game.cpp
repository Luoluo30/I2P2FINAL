#include "Game.h"
#include "Utils.h"
#include "data/DataCenter.h"
#include "data/OperationCenter.h"
#include "data/SoundCenter.h"
#include "data/ImageCenter.h"
#include "data/FontCenter.h"
#include "Player.h"
#include "Level.h"
#include "Character.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
// fixed settings
constexpr char game_icon_img_path[] = "./assets/image/game_icon.png";
constexpr char game_start_sound_path[] = "./assets/sound/growl.mp3";
constexpr char background_img_path[] = "./assets/image/StartBackground.jpg";
constexpr char menu_img_path[] = "./assets/image/cover.png";
constexpr char background_sound_path[] = "./assets/sound/winterscene.mp3";
constexpr char lose_sound_path[] = "./assets/sound/lose.mp3";
constexpr char win_sound_path[] = "./assets/sound/win.mp3";
constexpr char pass_img_path[] = "./assets/image/pass.jpg";
constexpr char fail_img_path[] = "./assets/image/fail.jpg";

/**
 * @brief Game entry.
 * @details The function processes all allegro events and update the event state to a generic data storage (i.e. DataCenter).
 * For timer event, the game_update and game_draw function will be called if and only if the current is timer.
 */
void
Game::execute() {
	DataCenter *DC = DataCenter::get_instance();
	// main game loop
	bool run = true;
	while(run) {
		// process all events here
		al_wait_for_event(event_queue, &event);
		switch(event.type) {
			case ALLEGRO_EVENT_TIMER: {
				run &= game_update();
				game_draw();
				break;
			} case ALLEGRO_EVENT_DISPLAY_CLOSE: { // stop game
				run = false;
				break;
			} case ALLEGRO_EVENT_KEY_DOWN: {
				DC->key_state[event.keyboard.keycode] = true;
				break;
			} case ALLEGRO_EVENT_KEY_UP: {
				DC->key_state[event.keyboard.keycode] = false;
				break;
			} case ALLEGRO_EVENT_MOUSE_AXES: {
				DC->mouse.x = event.mouse.x;
				DC->mouse.y = event.mouse.y;
				break;
			} case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
				DC->mouse_state[event.mouse.button] = true;
				break;
			} case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
				DC->mouse_state[event.mouse.button] = false;
				break;
			} default: break;
		}
	}
}

/**
 * @brief Initialize all allegro addons and the game body.
 * @details Only one timer is created since a game and all its data should be processed synchronously.
 */
Game::Game() {
	DataCenter *DC = DataCenter::get_instance();
	GAME_ASSERT(al_init(), "failed to initialize allegro.");

	// initialize allegro addons
	bool addon_init = true;
	addon_init &= al_init_primitives_addon();
	addon_init &= al_init_font_addon();
	addon_init &= al_init_ttf_addon();
	addon_init &= al_init_image_addon();
	addon_init &= al_init_acodec_addon();
	GAME_ASSERT(addon_init, "failed to initialize allegro addons.");

	// initialize events
	bool event_init = true;
	event_init &= al_install_keyboard();
	event_init &= al_install_mouse();
	event_init &= al_install_audio();
	GAME_ASSERT(event_init, "failed to initialize allegro events.");

	// initialize game body
	GAME_ASSERT(
		display = al_create_display(DC->window_width, DC->window_height),
		"failed to create display.");
	GAME_ASSERT(
		timer = al_create_timer(1.0 / DC->FPS),
		"failed to create timer.");
	GAME_ASSERT(
		event_queue = al_create_event_queue(),
		"failed to create event queue.");

	debug_log("Game initialized.\n");
	game_init();
}

/**
 * @brief Initialize all auxiliary resources.
 */

void Game::game_init() {
    DataCenter *DC = DataCenter::get_instance(); // 获取 DataCenter 单例
    SoundCenter *SC = SoundCenter::get_instance(); // 获取 SoundCenter 单例
    ImageCenter *IC = ImageCenter::get_instance(); // 获取 ImageCenter 单例
    FontCenter *FC = FontCenter::get_instance();   // 获取 FontCenter 单例
	std::cout << "inited game resourses..." << std::endl;
    // 设置窗口图标
    game_icon = IC->get(game_icon_img_path);
    al_set_display_icon(display, game_icon);
	std::cout << "game icon inited" << std::endl;
    // 注册事件源到事件队列
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	std::cout << "event registered" << std::endl;
    // 初始化音频设置
    SC->init();

    // 初始化字体设置
    FC->init();

    // 初始化用户界面
    ui = new UI();
    ui->init();

    // 初始化关卡和角色
    DC->level->init();
    DC->character->init();
	

    // 游戏开始界面设置
    background = IC->get(menu_img_path);
	level_background = IC->get(background_img_path);
	pass_background = IC->get(pass_img_path);
	fail_background = IC->get(fail_img_path);
    debug_log("Game state: change to START\n");
    state = STATE::START; // 设置初始状态为 START
    al_start_timer(timer); // 启动计时器
}

/**
 * @brief The function processes all data update.
 * @details The behavior of the whole game body is determined by its state.
 * @return Whether the game should keep running (true) or reaches the termination criteria (false).
 * @see Game::STATE
 */
bool
Game::game_update() {
	DataCenter *DC = DataCenter::get_instance();
	OperationCenter *OC = OperationCenter::get_instance();
	SoundCenter *SC = SoundCenter::get_instance();
	static ALLEGRO_SAMPLE_INSTANCE *background = nullptr;
	std::cout << "game resourses updated..." << std::endl;
	switch(state) {
		case STATE::START: {
			static bool is_played = false;
			static ALLEGRO_SAMPLE_INSTANCE *instance = nullptr;
			cout<<"case STATE::START"<<endl;
			if(!is_played) {
				instance = SC->play(game_start_sound_path, ALLEGRO_PLAYMODE_ONCE);
				DC->level->load_level(1);
				is_played = true;
				cout<<"!is_played"<<endl;
			}

			if(!SC->is_playing(instance)||DC->key_state[ALLEGRO_KEY_ENTER]) {
				debug_log("<Game> state: change to LEVEL\n");
				state = STATE::LEVEL;
			}
			break;
		} case STATE::LEVEL: {
			static bool BGM_played = false;
			cout<<"case STATE::LEVEL"<<endl;
			if(!BGM_played) {
				background = SC->play(background_sound_path, ALLEGRO_PLAYMODE_LOOP);
				BGM_played = true;
				cout<<"!BGM_played"<<endl;
			}

			if(DC->key_state[ALLEGRO_KEY_P] && !DC->prev_key_state[ALLEGRO_KEY_P]) {
				SC->toggle_playing(background);
				debug_log("<Game> state: change to PAUSE\n");
				state = STATE::PAUSE;
				
			}
			if(DC->level->remain_monsters() == 0 && DC->monsters.size() == 0) {
				debug_log("<Game> state: change to END\n");
				state = STATE::END;
			}
			if(DC->player->HP <= 0) {
				debug_log("<Game> state: change to END\n");
				state = STATE::FINAL_LOSE;
			}
			if(DC->player->watermelon == 40) {
				final_score = (int)DC->level->countdown_timer; 
				debug_log("<Game> state: change to END\n");
				state = STATE::FINAL_WIN;
			}
			break;
		} case STATE::PAUSE: {
			if(DC->key_state[ALLEGRO_KEY_P] && !DC->prev_key_state[ALLEGRO_KEY_P]) {
				SC->toggle_playing(background);
				debug_log("<Game> state: change to LEVEL\n");
				state = STATE::LEVEL;
			}
			break;
		} case STATE::FINAL_WIN:{
			static bool win_played = false;
			cout<<"case STATE::FINAL_WIN"<<endl;
			if(!win_played) {
				if (background != nullptr && al_get_sample_instance_playing(background)) {
            		al_stop_sample_instance(background);
        		}
				background = SC->play(win_sound_path, ALLEGRO_PLAYMODE_ONCE);
				win_played = true;
				cout<<"!BGM_played"<<endl;
			}
			if(DC->key_state[ALLEGRO_KEY_ENTER]) {
				debug_log("<Game> state: change to end\n");
				state = STATE::END;
			}
			break;
		} case STATE::FINAL_LOSE:{
			static bool lose_played = false;
			cout<<"case STATE::LEVEL"<<endl;
			if(!lose_played) {
				if (background != nullptr && al_get_sample_instance_playing(background)) {
            		al_stop_sample_instance(background);
        		}
				background = SC->play(lose_sound_path, ALLEGRO_PLAYMODE_ONCE);
				lose_played = true;
				cout<<"!BGM_played"<<endl;
			}
			if(DC->key_state[ALLEGRO_KEY_ENTER]) {
				debug_log("<Game> state: change to end\n");
				state = STATE::END;
			}
			break;
		} 
		case STATE::END: {
			return false;
		}
	}
	// If the game is not paused, we should progress update.
	if(state != STATE::PAUSE) {
		cout<<"state != STATE::PAUSE"<<endl;
		DC->player->update();
		cout<<"DC->player->update();"<<endl;
		SC->update();
		cout<<"SC->update();"<<endl;
		ui->update();
		cout<<"ui->update();"<<endl;
		DC->character->update();
		cout<<"character->update();"<<endl;
		if(state != STATE::START) {
			cout<<"state != STATE::START"<<endl;
			DC->level->update();
			cout<<"DC->level->update();"<<endl;
			if (OC == nullptr) {
    			std::cerr << "OperationCenter instance is nullptr!" << std::endl;
			} else {
    		std::cout << "OperationCenter instance exists!" << std::endl;
			}

			OC->update();
			cout<<"oc->update"<<endl;
		}
		cout<<"state != STATE::PAUSE end"<<endl;
	}
	// game_update is finished. The states of current frame will be previous states of the next frame.
	memcpy(DC->prev_key_state, DC->key_state, sizeof(DC->key_state));
	memcpy(DC->prev_mouse_state, DC->mouse_state, sizeof(DC->mouse_state));
	cout<<"game_update is finished"<<endl;
	return true;
}

/**
 * @brief Draw the whole game and objects.
 */

void Game::game_draw() {
    DataCenter *DC = DataCenter::get_instance();
    OperationCenter *OC = OperationCenter::get_instance();
    FontCenter *FC = FontCenter::get_instance();
	cout<<"game_draw"<<endl;
    // 清空屏幕
    al_clear_to_color(al_map_rgb(100, 100, 100));
	if(state == STATE::START){
		al_draw_bitmap(background, -50, 0, 0);
	}
    if(state == STATE::LEVEL) {
        // 绘制背景
        al_draw_bitmap(level_background, 0, 0, 0);
        if(DC->game_field_length < DC->window_width)
            al_draw_filled_rectangle(
                DC->game_field_length, 0,
                DC->window_width, DC->window_height,
                al_map_rgb(100, 149, 237));
        if(DC->game_field_length < DC->window_height)
            al_draw_filled_rectangle(
                0, DC->game_field_length,
                DC->window_width, DC->window_height,
                al_map_rgb(100, 149, 237));

        // 用户界面
        if(state == STATE::LEVEL) {
            DC->level->draw();
            DC->character->draw();
			cout<<"A"<<endl;
			cout<<"B"<<endl;

            ui->draw();
            OC->draw();
        }
    }
	if(state == STATE::FINAL_WIN){
		al_draw_bitmap(pass_background, 0, 0, 0);
		al_draw_textf(
		FC->courier_new[FontSize::LARGE], al_map_rgb(0,0, 20),
		550, 500,
		ALLEGRO_ALIGN_CENTER, "Score : %d ", final_score);
	}
	if(state == STATE::FINAL_LOSE){
		al_draw_bitmap(fail_background, 0, 0, 0);
	}
    // 状态切换
    switch(state) {
        case STATE::START: {
        } case STATE::LEVEL: {
            break;
        } case STATE::FINAL_WIN:{
		} case STATE::FINAL_LOSE:{
		} case STATE::PAUSE: {
            // 游戏暂停界面
            al_draw_filled_rectangle(0, 0, DC->window_width, DC->window_height, al_map_rgba(50, 50, 50, 64));
            // al_draw_text(
            //     FC->caviar_dreams[FontSize::LARGE], al_map_rgb(255, 255, 255),
            //     DC->window_width/2., DC->window_height/2.,
            //     ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");
            break;
        } case STATE::END: {
        }
    }
    al_flip_display();
}


Game::~Game() {
	delete ui;
    al_destroy_display(display); // 销毁显示窗口
    al_destroy_timer(timer);     // 销毁计时器
    al_destroy_event_queue(event_queue); // 销毁事件队列
}
