/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 32;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */

static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usrbh		    = 20;

static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=10" }; 
static const char dmenufont[]       = "monospace:size=10";

static const char col_darkblue[]    = "#10041c"; 
static const char col_test[]        = "#f0ffff"; 
static const char col_tag[]         = "#f5f5f5"; 

static const char *colors[][3]      = {
/*               fg         bg         border   */
[SchemeNorm] = { col_tag, col_darkblue, col_darkblue },
[SchemeSel]  = { col_tag, col_darkblue,  col_darkblue  }, 
};

static const char *const autostart[] = {
        "corectrl", NULL,
        "google-chrome-stable", NULL,
        "discord", NULL,
        "telegram-desktop", NULL,
	"lutris", NULL,
        "mouseserver", NULL,
        
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五" }; 

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
   { "Google-chrome",  NULL,       NULL,        1,            0,           -1 },
         { "discord",  NULL,       NULL,        2,            0,           -1 },
  { "TelegramDesktop", NULL,       NULL,        2,            0,           -1 },
          { "Lutris",  NULL,       NULL,        1 << 2,       0,           -1 },
           { "Steam",  NULL,       NULL,        1 << 2,       0,           -1 },
        { "corectrl",  NULL,       NULL,        1 << 3,       0,           -1 },
 
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     		arrange function */
	{ "",		tile },    /* first entry is default */
	{ "",		NULL },    /* no layout function means floating behavior */
	{ "",	     monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_darkblue, "-nf", col_tag, "-sb", col_tag, "-sf", col_darkblue, "-h", "22", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *scrlock[]  = { "slock", NULL };
static const char *mutecmd[]  = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "2%+", "unmute", NULL };
static const char *voldncmd[] = { "amixer", "-q", "set", "Master", "2%-", "unmute", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */

        /* Keybind Print */

        { MODKEY,                       XK_Print,  spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png") },
	{ 0,                            XK_Print,  spawn,          SHCMD("maim -u $HOME/Pictures/Screenshots/$(date +%d-%m-%y-%H:%M:%S)-SCREEN.png") },
	{ MODKEY,			XK_m,      spawn,          SHCMD("gotop") },
	{ MODKEY,			XK_e,      spawn,          SHCMD("thunar") },
	{ MODKEY,	                XK_l,      spawn,          {.v = scrlock } },
	{ MODKEY,                       XK_q,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = mutecmd } },
	{ MODKEY,                       XK_F5,     spawn,          {.v = voldncmd } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = volupcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
    	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)

        /* Keybind volume control */

/*	{ 0,	XF86XK_AudioMute,		spawn,	{.v = mutecmd } }, */
/*	{ 0,	XF86XK_AudioLowerVolume,	spawn,	{.v = voldncmd } }, */
/*	{ 0,	XF86XK_AudioRaiseVolume,	spawn,	{.v = volupcmd } }, */

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

