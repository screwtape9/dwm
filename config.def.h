/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 4;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;        /* vert inner gap between windows */
static const unsigned int gappoh    = 0;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "JetBrains Mono:style=Regular:size=16",
                                        "Symbols Nerd Font:style=2048-em:size=20",
                                        "JoyPixels:size=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrains Mono:style=Regular:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance              title           tags mask     isfloating   monitor */
	{ "FreeRDP",            NULL,                 NULL,           0,            1,           -1 },
	{ "gnome-calculator",   "gnome-calculator",   NULL,           0,            1,           -1 },
	{ "RabbitVCS",          "RabbitVCS",          NULL,           0,            1,           -1 },
	{ "org.gnome.Nautilus", "org.gnome.Nautilus", NULL,           0,            1,           -1 },
	{ "Sxiv",               "sxiv",               NULL,           0,            1,           -1 },
	{ "st-256color",        "st-256color",        "pulsemixer",   0,            1,           -1 },
	{ "Hello World",        "Hello World",        NULL,           0,            1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL }
};

/* key definitions */
#define MODKEY Mod4Mask
#define MOD2KEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *rabbit[]         = { "rabbitvcs", "browser", NULL };
static const char *chrocmd[]        = { "chromium", "--proxy-server=socks5://localhost:3434", "--host-resolver-rules=MAP * ~NOTFOUND , EXCLUDE localhost", NULL };
static const char *volumeupcmd[]    = { "pamixer", "--allow-boost", "-i", "3", NULL };
static const char *volumedowncmd[]  = { "pamixer", "--allow-boost", "-d", "3", NULL };
static const char *mutecmd[]        = { "pamixer", "-t", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd  } },
	{ MODKEY,                       XK_c,      spawn,          {.v = chrocmd  } },
	{ MODKEY,                       XK_v,      spawn,          {.v = rabbit   } },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show drun") },
	{ MOD2KEY,                      XK_Tab,    spawn,          SHCMD("rofi -show window") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("firefox --private-window") },
	{ MODKEY,                       XK_t,      spawn,          SHCMD("pidof -s picom && killall -9 picom || picom --backend glx &") },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("teams") },
	{ 0,                            XK_Print,  spawn,          SHCMD("maim ~/Pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_m,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MOD2KEY,                      XK_0,      togglegaps,     {0} },
	{ MOD2KEY|ShiftMask,            XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrgaps,       {.i = -1 } },
	{ MOD2KEY,                      XK_o,      incrogaps,      {.i = +1 } },
	{ MOD2KEY|ShiftMask,            XK_o,      incrogaps,      {.i = -1 } },
	{ MOD2KEY,                      XK_6,      incrihgaps,     {.i = +1 } },
	{ MOD2KEY|ShiftMask,            XK_6,      incrihgaps,     {.i = -1 } },
	{ MOD2KEY,                      XK_7,      incrivgaps,     {.i = +1 } },
	{ MOD2KEY|ShiftMask,            XK_7,      incrivgaps,     {.i = -1 } },
	{ MOD2KEY,                      XK_8,      incrohgaps,     {.i = +1 } },
	{ MOD2KEY|ShiftMask,            XK_8,      incrohgaps,     {.i = -1 } },
	{ MOD2KEY,                      XK_9,      incrovgaps,     {.i = +1 } },
	{ MOD2KEY|ShiftMask,            XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MOD2KEY,                      XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MOD2KEY,                      XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MOD2KEY,                      XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("st -g \"176x20+398+508\" -e pulsemixer") },
	{ 0, XF86XK_AudioMute,                     spawn,          {.v = mutecmd } },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = volumeupcmd } },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          {.v = volumedowncmd } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

