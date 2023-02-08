/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=12", "SauceCodePro Nerd Font Mono:size=13"  };
static const char dmenufont[]       = "Hack Nerd Font Mono:size=12";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#434c5e";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#eceff4";
static const char col_cyan[]        = "#5e81ac";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	// class         instance      title      tags mask    isfloating   monitor
	{ NULL,          "Navigator",  NULL,      1,           0,           -1 },
	{ "discord",     NULL,         NULL,      1 << 8,      0,           -1 },
	{ "easyeffects", NULL,         NULL,      1 << 4,      0,           -1 },
	{ "Pavucontrol", NULL,         NULL,      1 << 4,      0,           -1 },
	{ "Mindustry",   NULL,         NULL,      1 << 1,      0,           -1 },
	//  { "Gimp",     NULL,       NULL,      0,            1,           -1 },
	//  { "Firefox",  NULL,       NULL,      1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int mainmon = 0; /* xsetroot will only change the bar on this monitor */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// include shiftview patch
#include "./shiftview.c"

// include something for keyboard (?)
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dapps[] = { "dapps", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *screenshot[] = { "screenshot", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *reshut[] = { "reshut", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x30", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dapps } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	// { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_p,      shiftview,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	// { MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	// { MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	// { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY|ShiftMask,			        XK_s,      spawn,	         {.v = screenshot} },              // screenshot
	{ MODKEY,	   		                XK_w,      spawn,		       SHCMD("$BROWSER") },              // open browser
	{ MODKEY|ShiftMask,			        XK_b,      spawn,	         SHCMD("nsxiv -ft ~/Pictures/wallpapers")}, // set wallpaper
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,   SHCMD("tostadora light inc")},
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,   SHCMD("tostadora light dec")},
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,   SHCMD("tostadora sound inc")},
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,   SHCMD("tostadora sound dec")},
	{ 0,                            XF86XK_AudioMute,          spawn,   SHCMD("tostadora sound mute")},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("killall xinit") },
	{ MODKEY|ShiftMask,			        XK_x,      spawn,	         {.v = reshut }},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
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

