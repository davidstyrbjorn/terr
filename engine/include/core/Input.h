#pragma once

namespace terr {

	enum EventType {
		KEY_PRESSED,
		KEY_RELEASED,
		MOUSE_DOWN,
		MOUSE_UP,
		WINDOW_RESIZE
	};

	static int KEYS[1026];

	struct Event {
		EventType eventType;
		int key; // Keyboard 
		int button; // Mouse
	};


	/* The unknown key */
#define GLFW_KEY_UNKNOWN            -1

/* Printable keys */
#define TERR_KEY_SPACE              32
#define TERR_KEY_APOSTROPHE         39  /* ' */
#define TERR_KEY_COMMA              44  /* , */
#define TERR_KEY_MINUS              45  /* - */
#define TERR_KEY_PERIOD             46  /* . */
#define TERR_KEY_SLASH              47  /* / */
#define TERR_KEY_0                  48
#define TERR_KEY_1                  49
#define TERR_KEY_2                  50
#define TERR_KEY_3                  51
#define TERR_KEY_4                  52
#define TERR_KEY_5                  53
#define TERR_KEY_6                  54
#define TERR_KEY_7                  55
#define TERR_KEY_8                  56
#define TERR_KEY_9                  57
#define TERR_KEY_SEMICOLON          59  /* ; */
#define TERR_KEY_EQUAL              61  /* = */
#define TERR_KEY_A                  65
#define TERR_KEY_B                  66
#define TERR_KEY_C                  67
#define TERR_KEY_D                  68
#define TERR_KEY_E                  69
#define TERR_KEY_F                  70
#define TERR_KEY_G                  71
#define TERR_KEY_H                  72
#define TERR_KEY_I                  73
#define TERR_KEY_J                  74
#define TERR_KEY_K                  75
#define TERR_KEY_L                  76
#define TERR_KEY_M                  77
#define TERR_KEY_N                  78
#define TERR_KEY_O                  79
#define TERR_KEY_P                  80
#define TERR_KEY_Q                  81
#define TERR_KEY_R                  82
#define TERR_KEY_S                  83
#define TERR_KEY_T                  84
#define TERR_KEY_U                  85
#define TERR_KEY_V                  86
#define TERR_KEY_W                  87
#define TERR_KEY_X                  88
#define TERR_KEY_Y                  89
#define TERR_KEY_Z                  90
#define TERR_KEY_LEFT_BRACKET       91  /* [ */
#define TERR_KEY_BACKSLASH          92  /* \ */
#define TERR_KEY_RIGHT_BRACKET      93  /* ] */
#define TERR_KEY_GRAVE_ACCENT       96  /* ` */
#define TERR_KEY_WORLD_1            161 /* non-US #1 */
#define TERR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define TERR_KEY_ESCAPE             256
#define TERR_KEY_ENTER              257
#define TERR_KEY_TAB                258
#define TERR_KEY_BACKSPACE          259
#define TERR_KEY_INSERT             260
#define TERR_KEY_DELETE             261
#define TERR_KEY_RIGHT              262
#define TERR_KEY_LEFT               263
#define TERR_KEY_DOWN               264
#define TERR_KEY_UP                 265
#define TERR_KEY_PAGE_UP            266
#define TERR_KEY_PAGE_DOWN          267
#define TERR_KEY_HOME               268
#define TERR_KEY_END                269
#define TERR_KEY_CAPS_LOCK          280
#define TERR_KEY_SCROLL_LOCK        281
#define TERR_KEY_NUM_LOCK           282
#define TERR_KEY_PRINT_SCREEN       283
#define TERR_KEY_PAUSE              284
#define TERR_KEY_F1                 290
#define TERR_KEY_F2                 291
#define TERR_KEY_F3                 292
#define TERR_KEY_F4                 293
#define TERR_KEY_F5                 294
#define TERR_KEY_F6                 295
#define TERR_KEY_F7                 296
#define TERR_KEY_F8                 297
#define TERR_KEY_F9                 298
#define TERR_KEY_F10                299
#define TERR_KEY_F11                300
#define TERR_KEY_F12                301
#define TERR_KEY_F13                302
#define TERR_KEY_F14                303
#define TERR_KEY_F15                304
#define TERR_KEY_F16                305
#define TERR_KEY_F17                306
#define TERR_KEY_F18                307
#define TERR_KEY_F19                308
#define TERR_KEY_F20                309
#define TERR_KEY_F21                310
#define TERR_KEY_F22                311
#define TERR_KEY_F23                312
#define TERR_KEY_F24                313
#define TERR_KEY_F25                314
#define TERR_KEY_KP_0               320
#define TERR_KEY_KP_1               321
#define TERR_KEY_KP_2               322
#define TERR_KEY_KP_3               323
#define TERR_KEY_KP_4               324
#define TERR_KEY_KP_5               325
#define TERR_KEY_KP_6               326
#define TERR_KEY_KP_7               327
#define TERR_KEY_KP_8               328
#define TERR_KEY_KP_9               329
#define TERR_KEY_KP_DECIMAL         330
#define TERR_KEY_KP_DIVIDE          331
#define TERR_KEY_KP_MULTIPLY        332
#define TERR_KEY_KP_SUBTRACT        333
#define TERR_KEY_KP_ADD             334
#define TERR_KEY_KP_ENTER           335
#define TERR_KEY_KP_EQUAL           336
#define TERR_KEY_LEFT_SHIFT         340
#define TERR_KEY_LEFT_CONTROL       341
#define TERR_KEY_LEFT_ALT           342
#define TERR_KEY_LEFT_SUPER         343
#define TERR_KEY_RIGHT_SHIFT        344
#define TERR_KEY_RIGHT_CONTROL      345
#define TERR_KEY_RIGHT_ALT          346
#define TERR_KEY_RIGHT_SUPER        347
#define TERR_KEY_MENU               348

#define TERR_MOUSE_BUTTON_1         0
#define TERR_MOUSE_BUTTON_2         1
#define TERR_MOUSE_BUTTON_3         2
#define TERR_MOUSE_BUTTON_4         3
#define TERR_MOUSE_BUTTON_5         4
#define TERR_MOUSE_BUTTON_6         5
#define TERR_MOUSE_BUTTON_7         6
#define TERR_MOUSE_BUTTON_8         7
#define TERR_MOUSE_BUTTON_LAST      TERR_MOUSE_BUTTON_8
#define TERR_MOUSE_BUTTON_LEFT      TERR_MOUSE_BUTTON_1
#define TERR_MOUSE_BUTTON_RIGHT     TERR_MOUSE_BUTTON_2
#define TERR_MOUSE_BUTTON_MIDDLE    TERR_MOUSE_BUTTON_3

#define TERR_KEY_LAST               TERR_KEY_MENU

}