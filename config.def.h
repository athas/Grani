static char *useragent      = "Mozilla/5.0 (Linux; en-US) AppleWebKit/534.6 (KHTML, like Gecko) Chrome/7.0.500.0 Safari/534.6";
static char *stylefile      = "style.css";
static char *scriptfile     = "script.js";
static char *cookiefile     = "cookies.txt";
static time_t sessiontime   = 3600*24*30;

#define SETPROP_PROG(p, q, prog)                                        \
    { .v = (char *[]){ "/bin/sh", "-c",                                 \
                       "prop=\"$(xprop -id $2 $0 | cut -d '\"' -f 2 | $3)\" &&" \
                       "xprop -id $2 -f $1 8s -set $1 \"$prop\"",       \
                       p, q, winid, prog, NULL } }
#define SETPROP(p, q) SETPROP_PROG(p,q,"sinmenu")
#define BROWSE(p) { .v = (char *[]){ "/bin/sh", "-c", "grani-browse $1 $0 < /dev/null", p, winid, NULL } }
#define STRING(f) { .v = (char*[]){ f } }
#define DOWNLOAD(d, f) { .v = (char *[]){ "/bin/sh", "-c", "grani-download $0 $1 < /dev/null", d, NULL } }

#define CTRL GDK_CONTROL_MASK
#define SHIFT GDK_SHIFT_MASK
#define META GDK_MOD1_MASK

/* modifier 0 means no modifier */
static Key keys[] = {
    /* modifier	            keyval      function    arg             Focus */
    /* Defaults */
    { CTRL|SHIFT,           GDK_j,      zoom,       { .i = -1 } },
    { CTRL|SHIFT,           GDK_k,      zoom,       { .i = +1 } },
    { CTRL|SHIFT,           GDK_i,      zoom,       { .i = 0  } },
    { CTRL,                 GDK_o,      source,     { 0 } },
    /* My own */
    { SHIFT,                GDK_r,      reload,     { .b = TRUE } },
    { 0,                    GDK_r,      reload,     { .b = FALSE } },
    { CTRL,                 GDK_y,      clipboard,  { .b = TRUE } },
    { META,                 GDK_w,      clipboard,  { .b = FALSE } },
    { CTRL,                 GDK_g,      stop,       { 0 } },
    { SHIFT,                GDK_f,      navigate,   { .i = +1 } },
    { SHIFT,                GDK_b,      navigate,   { .i = -1 } },
    { CTRL,                 GDK_n,      scroll,     { .i = +1 } },
    { CTRL,                 GDK_p,      scroll,     { .i = -1 } },
    { CTRL,                 GDK_s,      spawn,      SETPROP("_GRANI_FIND", "_GRANI_FIND") },
    { 0,                    GDK_g,      spawn,      SETPROP_PROG("_GRANI_URI", "_GRANI_GO", "grani-field") },
    { 0,                    GDK_h,      spawn,      BROWSE("history") },
    { 0,                    GDK_b,      spawn,      BROWSE("bookmark") },
    { 0,                    GDK_x,      spawn,      BROWSE("del") },
    { SHIFT,                GDK_i,      spawn,      BROWSE("info") },
    { CTRL|SHIFT,           GDK_g,      spawn,      BROWSE("go_raw") },
    { CTRL,                 GDK_f,      eval,       STRING("hintMode()") },
    { CTRL|SHIFT,           GDK_f,      eval,       STRING("hintMode(true)") },
    { CTRL,                 GDK_c,      eval,       STRING("removeHints()") },
    { CTRL,                 GDK_z,      suspend,    { 0 } },
};
