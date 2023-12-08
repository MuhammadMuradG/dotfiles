/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const double activeopacity   = 0.85f;    /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.7f;     /* Window opacity when it's unfocused (0 <= opacity <= 1) */
static const char *fonts[]          = { "RobotoMono Nerd Font:pixelsize=10:style=bold" };
static const char dmenufont[]       = "RobotoMono Nerd Font:pixelsize=10";
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
	/* class          instance         title      tags mask     iscentered    isfloating    focusopacity    unfocusopacity    monitor */
	{ "st-256color",  "st-256color",   "rover",   0,            1,            1,            activeopacity,  inactiveopacity,  -1 },
};

/* layout(s) */
static const float mfact        = 0.7;  /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]        = { "st", NULL };
static const char *explorer[]       = { "st", "rover", NULL };
static const char *browser[]        = { "firefox", "-p", NULL };
static const char *lockcmd[]        = { "slock", NULL };
static const char *pdfviewer[]      = { "evince", NULL };
static const char *volumemutecmd[]  = { "mixer", "vol.volume=0", NULL };
static const char *volumeupcmd[]    = { "mixer", "vol.volume=+0.05", NULL };
static const char *volumedowncmd[]  = { "mixer", "vol.volume=-0.05", NULL };

static Key keys[] = {

	/* modifier                     key         function              custom argument */
	{ MODKEY|ShiftMask,             XK_x,       spawn,                {.v = explorer } },
	{ MODKEY|ShiftMask,             XK_w,       spawn,                {.v = browser } },
	{ MODKEY|ShiftMask,             XK_s,       spawn,                {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_v,       spawn,                {.v = pdfviewer } },
	{ MODKEY|ShiftMask,             XK_F11,     spawn,                {.v = volumemutecmd } },
	{ MODKEY|ShiftMask,             XK_F9,      spawn,                {.v = volumedowncmd } },
	{ MODKEY|ShiftMask,             XK_F10,     spawn,                {.v = volumeupcmd } },
	{ MODKEY|ShiftMask,             XK_a,       changefocusopacity,   {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_y,       changefocusopacity,   {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_z,       changeunfocusopacity, {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_m,       changeunfocusopacity, {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_minus,   setgaps,              {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_plus,    setgaps,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,   setgaps,              {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_F2,      spawn,                SHCMD("xrandr --output LVDS-1 --gamma 1.0:0.8:0.6 --brightness 0.9") },
	{ MODKEY|ShiftMask,             XK_F3,      spawn,                SHCMD("xrandr --output LVDS-1 --gamma 1:1:1 --brightness 1") },

	/* modifier                     key         function              argument */
	{ MODKEY,                       XK_p,       spawn,                {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,  spawn,                {.v = termcmd } },
	{ MODKEY,                       XK_b,       togglebar,            {0} },
	{ MODKEY,                       XK_j,       focusstack,           {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,           {.i = -1 } },
	{ MODKEY,                       XK_i,       incnmaster,           {.i = +1 } },
	{ MODKEY,                       XK_d,       incnmaster,           {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,             {.f = -0.03} },
	{ MODKEY,                       XK_l,       setmfact,             {.f = +0.03} },
	{ MODKEY|ShiftMask,             XK_h,       setcfact,             {.f = +0.03} },
	{ MODKEY|ShiftMask,             XK_l,       setcfact,             {.f = -0.03} },
	{ MODKEY|ShiftMask,             XK_o,       setcfact,             {.f =  0.00} },
	{ MODKEY,                       XK_Return,  zoom,                 {0} },
	{ MODKEY,                       XK_Tab,     view,                 {0} },
	{ MODKEY|ShiftMask,             XK_c,       killclient,           {0} },
	{ MODKEY,                       XK_t,       setlayout,            {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,       setlayout,            {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,       setlayout,            {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,   setlayout,            {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating,       {0} },
	{ MODKEY,                       XK_0,       view,                 {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,                  {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,             {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,               {.i = +1 } },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	TAGKEYS(                        XK_8,                             7)
	TAGKEYS(                        XK_9,                             8)
	{ MODKEY|ShiftMask,             XK_q,       quit,                 {0} },
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

