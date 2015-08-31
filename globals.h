/********************************************************************************************************
 *                                     Definiçao de estados do programa
 ********************************************************************************************************/
typedef void (*state_function_t)();
typedef void (*event_t)();
state_function_t RUNNING_STATE;

#define STATE_HOUR &update_hour
#define STATE_MENU &update_menu
#define STATE_ALARM &update_alarm
#define STATE_DREAM &update_dream
#define STATE_DREAM_WAITING &update_dream_waiting
#define STATE_DREAM_FLASHING &update_dream_flashing
#define STATE_CFG_HOUR &update_cfg_hour
#define STATE_CFG_ALARM &update_cfg_alarm
#define STATE_CFG_DREAM &update_cfg_dream
#define STATE_DEBUG &update_debug


/********************************************************************************************************
 *                                     Definiçao de macros
 ********************************************************************************************************/
#define menu_transition() display_write("----"); delay(100)
