/*
	 DWM 6.1		
   Config by pixxuser
			
*/			
#include <X11/XF86keysym.h>
#include "restart.c"
#include "zoomswap.c"

// Appearance
#define NUMCOLORS 9
static const char colors[NUMCOLORS][MAXCOLORS][9] = {
//	   Border    Foreground	Background
	{ "#383838", "#FCFCFC", "#171717" }, // Normal
	{ "#E8E8E8", "#222222", "#FCFCFC" }, // Selected
	{ "#b43030", "#f5f5f5", "#b23450" }, // Urgent
	{ "#212121", "#f5f5f5", "#14161A" }, // Occupied
	{ "#212121", "#ab7438", "#0b0606" }, // Yellow
	{ "#212121", "#475971", "#0b0606" }, // Blue
	{ "#212121", "#694255", "#0b0606" }, // Cyan
	{ "#212121", "#3e6868", "#0b0606" }, // Magenta
	{ "#212121", "#cfa696", "#0b0606" }, // Grey
};

static const char *fonts[]			= {	"drift:pixelsize=9",
							"Siji"			
};
static const unsigned int borderpx 		= 2;	// Border pixel of windows
static const unsigned int snap 			= 8;	// Snap pixel
static const unsigned int tagpadding 		= 15;	// Space between tags
static const unsigned int tagspacing 		= 0;	// Inner padding of tags
static const unsigned int gappx			= 8;	// Gaps pixel between windows
static const unsigned int systraypinning 	= 0;	// 0 means sloppy systray follows selected monitor
static const unsigned int systrayspacing 	= 0;	// Systray spacing 
static const int systraypinningfailfirst 	= 1;	// 0 means display systray on the last monitor
static const int showsystray 			= 1;	// 0 means no systray 
static const Bool showbar 			= True;	// False means no bar
static const Bool topbar 			= True;	// False means bottom bar

// Tags
static const char *tags[] = { "MAIN  ", "WEB  ", "DEVEL  ", "TOOLS  " };

static const Rule rules[] = {
//	 Class		Instance    Title       Tags	      Isfloating   Monitor 
	{ "Gcolor2",	NULL,       NULL,       0,            1,           -1 },
	{ "Inkscape",	NULL,       NULL,       0,	      0,           -1 },
};

// Layout 
#include "bstack.c"
#include "bstackhoriz.c"
#include "gaplessgrid.c"
#include "horizgrid.c"

static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
//	 Symbol    Arrange function */
	{ "",      tile },    // Default
	{ "",     NULL },    // Float
	{ "",      monocle },
	{ "",    bstack },
	{ "",    bstackhoriz },
	{ "",    gaplessgrid },
	{ "",    horizgrid },
};

// Key Definitions
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

// Helper
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Commands
static char dmenumon[2] = "0";
static const char *dmenucmd[]   = { "dmenu_run", "-b", "-p", "Menu", "-fn", "gmnterm", "-sf", "#171717", "-sb", "#FCFCFC", NULL };
static const char *termcmd[]    = { "urxvt", NULL };
// Sound
static const char *volup[]      = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldown[]    = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
// Screenshot
static const char *scrot[]	= { "scrot", NULL };

// Keybind
static Key keys[] = {
//	 Modifier			Key				Function        Argument
	{ MODKEY|ShiftMask,             XK_d,				spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,			spawn,          {.v = termcmd } },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,          {.v = volup } },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,          {.v = voldown } },
	{ 0,				XK_Print,			spawn,		{.v = scrot } },
	{ MODKEY|ShiftMask,		XK_b,				togglebar,	{0} },
	{ MODKEY,                       XK_j,				focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,				focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,				movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,				movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,				incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,				incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,				setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,				setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_Up,				setcfact,	{.f = +0.25} },
	{ MODKEY|ShiftMask,		XK_Down,			setcfact,	{.f = -0.25} },
	{ MODKEY|ShiftMask,		XK_o,				setcfact,	{.f =  0.00} },
	{ MODKEY,                       XK_Return,			zoom,           {0} },
	{ MODKEY,                       XK_Tab,				view,           {0} },
	{ MODKEY,			XK_w,				killclient,     {0} },
	{ MODKEY,                       XK_t,				setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,				setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,				setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,				setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_d,				setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_g,				setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_h,				setlayout,      {.v = &layouts[6]} },
	{ MODKEY,			XK_u,				togglefullscreen,{0} },
	{ MODKEY|ShiftMask,		XK_space,			togglefloating,	{0} },
	{ MODKEY,			XK_0,				view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,				tag,		{.ui = ~0 } },
	{ MODKEY,			XK_comma,			focusmon,	{.i = -1 } },
	{ MODKEY,			XK_period,			focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_comma,			tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period,			tagmon,		{.i = +1 } },
	TAGKEYS(			XK_1,				0)
	TAGKEYS(			XK_2,				1)
	TAGKEYS(			XK_3,				2)
	TAGKEYS(			XK_4,				3)
	{ MODKEY|ShiftMask,		XK_q,				quit,		{0} },
	{ MODKEY|ShiftMask,		XK_r,				restart,	{0} },
};

// Button Definitions
static Button buttons[] = {
//	 Click                event mask      button          function        argument
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
