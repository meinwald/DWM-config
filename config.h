/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#cccccc";
static const char normbgcolor[]     = "#cccccc";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#0066ff";
static const char selbgcolor[]      = "#0066ff";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
#define MKTAGS(a,b,c,d,e,f,g,h,i) enum Tag{a,b,c,d,e,f,g,h,i}; static const char *tags[] = {#a,#b,#c,#d,#e,#f,#g,#h,#i}
MKTAGS(Web,Mail,Terminal,IM,Media,GIMP,Office,Game,T9);
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << GIMP,       True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << Web,        False,       -1 },
	{ "Aurora",   NULL,       NULL,       1 << Web,        False,       -1 },
	{ "Thunderbird", NULL,    NULL,       1 << Mail,       False,       -1 },
	{ "Earlybird", NULL,      NULL,       1 << Mail,       False,       -1 },
	{ "Pidgin",   NULL,       NULL,       1 << IM,         False,       -1 },
	{ "Evince",   NULL,       NULL,       1 << Media,      False,       -1 },
	{ "Xpdf",     NULL,       NULL,       1 << Media,      False,       -1 },
	{ "Vlc",      NULL,       NULL,       1 << Media,      False,       -1 },
	{ "Mplayer",  NULL,       NULL,       1 << Media,      False,       -1 },
	{ "Eog",      NULL,       NULL,       1 << Media,      False,       -1 },
	{ "Gnome-terminal", NULL, NULL,       1 << Terminal,   False,       -1 },
	{ NULL,       "xterm",    NULL,       1 << Terminal,   False,       -1 },
	{ "libreoffice-writer", NULL, NULL,   1 << Office,     False,       -1 },
	{ "libreoffice-math", NULL, NULL,     1 << Office,     False,       -1 },
	{ "libreoffice-calc", NULL, NULL,     1 << Office,     False,       -1 },
	{ "libreoffice-base", NULL, NULL,     1 << Office,     False,       -1 },
	{ "libreoffice-draw", NULL, NULL,     1 << Office,     False,       -1 },
	{ "libreoffice-startcenter", NULL, NULL, 1 << Office,  False,       -1 },
	{ "libreoffice-impress", NULL, NULL,   1 << Office,    False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };
static const char *quitXcmd[] = { "killall", "dwm", NULL };

/* shift selected tags i places, wrapping around */
void viewNext(const Arg *arg) {
    unsigned int cur = selmon->tagset[selmon->seltags];
    int i = arg->i;
    if (arg->i < 0) {
        Arg a = {.ui = (cur >> -i) | (cur << (LENGTH(tags) + i))};
        view(&a);
    }
    else {
        Arg a = {.ui = (cur << i) | (cur >> (LENGTH(tags) - i))};
        view(&a);
    }
}

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY|ShiftMask|ControlMask, XK_q,      spawn,          {.v = quitXcmd} },
	{ MODKEY|ControlMask,           XK_Left,   viewNext,       {.i = -1} },
	{ MODKEY|ControlMask,           XK_Right,  viewNext,       {.i = +1} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
	{ ClkTagBar,            0,              Button4,        viewNext,       {.i = -1} },
	{ ClkTagBar,            0,              Button5,        viewNext,       {.i = +1} },
};

