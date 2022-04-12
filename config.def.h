/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 14;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=14", "fontawesome:size=14" };
static const char dmenufont[]	    = "JetBrains Mono:size=14";
#include "/home/senn/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tags[] = { "=(", "._.", ":)", "[~.~]", "B)"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "st", NULL };
static const char *screencmd[] = {"scrot", "/home/senn/Pictures/screenshots/screenshot.jpg", "--silent", NULL};
static const char *refbarcmd[] = { "refbar", NULL };

/* multimedia keys */
static const char *mutecmd[] = { "amixer", "-c", "1", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-c", "1", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-c", "1", "-q", "set", "Master", "5%-", "unmute", NULL };
/* static const char *miccmd[] = { "amixer", "set", "Capture", "toggle", NULL }; */

/* brightness keys */
static const char *brupcmd[] = { "sudo", "light", "-A", "10", NULL };
static const char *brdowncmd[] = { "sudo", "light", "-U", "10", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument 		explanation*/
	{ MODKEY,		       	XK_d,      spawn,          {.v = dmenucmd } }, 	/* d [open Dmenu] */
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } }, 	/* ENTER [open terminal] */
	{ MODKEY,                       XK_b,      togglebar,      {0} },		/* b [toggle status bar] */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },	/* j [cycle up  windows] */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },	/* k [cycle down windows] */
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },	/* o [increase master] */
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },	/* SHIFT + o [decrease master] */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },	/* h [increase window width] */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },	/* l [decrease window width] */
	{ MODKEY,                       XK_space,  zoom,           {0} }, 		/* SPACE [Make selected window the master] */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		XK_q,      killclient,     {0} }, 		/* kill window */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },/*t [tiling layout] */
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },/*y [floating layout] */
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },/*u [monocle layout] */
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },/*r [fibonacci layout] */
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },/*shift+ r [dwindle layout] */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -4 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +4 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = gappx } },
	{ MODKEY,			XK_Print,  spawn,	   {.v = screencmd } },
	{ 0, XF86XK_AudioMute, 			   spawn, 	   {.v = mutecmd } },
	{ 0, XF86XK_AudioLowerVolume, 		   spawn, 	   {.v = voldowncmd } },
	{ 0, XF86XK_AudioRaiseVolume, 		   spawn, 	   {.v = volupcmd } },
	{ 0, XF86XK_MonBrightnessUp, 		   spawn, 	   {.v = brupcmd} },
	{ 0, XF86XK_MonBrightnessDown, 		   spawn, 	   {.v = brdowncmd} },
	{ 0, XF86XK_AudioLowerVolume, 		   spawn, 	   {.v = refbarcmd} },
	{ 0, XF86XK_AudioRaiseVolume, 		   spawn, 	   {.v = refbarcmd} },
	{ 0, XF86XK_MonBrightnessUp, 		   spawn, 	   {.v = refbarcmd} },
	{ 0, XF86XK_MonBrightnessDown, 		   spawn, 	   {.v = refbarcmd} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

