/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const int showbar                   = 1;  /* 0 means no bar */
static const int topbar                    = 1;  /* 0 means bottom bar */
static const char *fonts[]                 = {"Iosevka Nerd Font Propo:size=12"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xebdbc2ff, 0x111111ff, 0x444444ff },
	[SchemeSel]  = { 0x111111ff, 0xebdbb2ff, 0x98971aff },
	[SchemeUrg]  = { 0,          0,          0xcc241dff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{}
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "gb",
};

static const int repeat_rate = 50;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 0;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.6;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

static const int hide_cursor_when_typing = 1;

/* If you want to use the alt key for MODKEY, use WLR_MODIFIER_ALT */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* helper for defining wmenu scripts with pass-through args */
#define WMENU(script) (const char*[]){ script, "-i", "-f", "Iosevka Nerd Font Propo 12", "-N", "111111", "-n", "988888", "-M", "111111", "-m", "ebdbc2", "-S", "ebdbc2", "-s", "111111", NULL }

/* commands */
static const char *launch[] =    WMENU("wmenu-run");
static const char *power[] =     WMENU("wmenu-power");
static const char *mount[] =     WMENU("wmenu-mount");
static const char *bt[] =	     WMENU("wmenu-bt");
static const char *emoji[] =     WMENU("wmenu-emoji");
static const char *bitw[] =      WMENU("wmenu-bw");
static const char *clipboard[] = WMENU("wmenu-clip");
static const char *prtsc[] =     WMENU("wmenu-screenshot");
static const char *term[] =    { "foot", "tmux", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *volup[]	 = { "volume", "up", NULL };
static const char *voldown[] = { "volume", "down", NULL };
static const char *volmute[] = { "volume", "mute", NULL };
static const char *briup[] =   { "brightnessctl", "set", "+10%", NULL };
static const char *bridown[] = { "brightnessctl", "set", "10%-", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes. */
	/* modifier                  key                  function          argument */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       spawn,            {.v = launch} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           spawn,            {.v = power} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_m,           spawn,            {.v = mount} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_b,           spawn,            {.v = bt} },
	{ MODKEY,					 XKB_KEY_period,      spawn,            {.v = emoji} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_p,			  spawn,            {.v = bitw} },
	{ 0,						 XKB_KEY_Print,		  spawn,            {.v = prtsc} },
	{ MODKEY,					 XKB_KEY_v,			  spawn,            {.v = clipboard} },
	{ MODKEY,					 XKB_KEY_space,       spawn,            {.v = term} },
	{ MODKEY,					 XKB_KEY_b,			  spawn,            {.v = browser} },
	{ MODKEY,                    XKB_KEY_j,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,           focusstack,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_n,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_e,           focusstack,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_m,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_i,           setmfact,         {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_plus,        incnmaster,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_minus,       incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_z,			  zoom,             {0} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },
	{ MODKEY,					 XKB_KEY_q,           killclient,       {0} },
	{ MODKEY,					 XKB_KEY_t,			  togglefloating,   {0} },
	{ MODKEY,                    XKB_KEY_f,           togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_Down,        moveresizekb,     {.v = (int []){ 0, 100, 0, 0 }}},
	{ MODKEY,                    XKB_KEY_Up,          moveresizekb,     {.v = (int []){ 0, -100, 0, 0 }}},
	{ MODKEY,                    XKB_KEY_Right,       moveresizekb,     {.v = (int []){ 100, 0, 0, 0 }}},
	{ MODKEY,                    XKB_KEY_Left,        moveresizekb,     {.v = (int []){ -100, 0, 0, 0 }}},
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Down,        moveresizekb,     {.v = (int []){ 0, 0, 0, 100 }}},
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Up,          moveresizekb,     {.v = (int []){ 0, 0, 0, -100 }}},
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,       moveresizekb,     {.v = (int []){ 0, 0, 100, 0 }}},
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,        moveresizekb,     {.v = (int []){ 0, 0, -100, 0 }}},
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_Return,      focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_BackSpace,   focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,	  tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_BackSpace,   tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY,                    XKB_KEY_Delete,      tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_quotedbl,                      1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_sterling,                      2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),
	{ 0,					     XKB_KEY_XF86AudioLowerVolume,  spawn,  {.v = voldown} },
	{ 0,					     XKB_KEY_XF86AudioRaiseVolume,  spawn,  {.v = volup} },
	{ 0,					     XKB_KEY_XF86AudioMute,	        spawn,	{.v = volmute} },
	{ 0,					     XKB_KEY_XF86MonBrightnessUp,   spawn,  {.v = briup} },
	{ 0,					     XKB_KEY_XF86MonBrightnessDown, spawn,	{.v = bridown} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = term} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
