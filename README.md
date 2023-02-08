# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.

## My Patches (In order)

- [fullgaps](https://dwm.suckless.org/patches/fullgaps)
- [no border](https://dwm.suckless.org/patches/noborder/)
- [rotate stack](https://dwm.suckless.org/patches/rotatestack/)
- [always center](https://dwm.suckless.org/patches/alwayscenter/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [shiftview](https://lists.suckless.org/dev/1104/7590.html)
- [mainmon](https://dwm.suckless.org/patches/mainmon/)
- [warp](https://dwm.suckless.org/patches/warp/)
- [scratchpad](https://dwm.suckless.org/patches/scratchpad/)
- [notitle](https://dwm.suckless.org/patches/notitle/)

## Exploding Windows

With `skippy-xd` you can explode your windows and warp to whatever window you want.

## Media keys

Here is a helpful [link](https://gist.github.com/palopezv/efd34059af6126ad970940bcc6a90f2e)

for ricing and colorscheme

```c
static const char *colors[][3]      = {
	/*  name                fg              bg         border   */
    [SchemeNorm]     = { col_gray4,      col_gray1,  col_gray2 },
    [SchemeSel]      = { col_gray4,      col_blue,   col_blue  },
    //                 { text,           background, not used but can't be empty}
    [SchemeStatus]   = { col_gray4,      col_gray1,  "#000000"  }, // Statusbar right
    [SchemeTagsSel]  = { col_info_blue,  col_gray1,  "#000000"  }, // Tagbar left selected
    [SchemeTagsNorm] = { col_gray3,      col_gray1,  "#000000"  }, // Tagbar left unselected
    [SchemeInfoSel]  = { col_gray3,      col_bg_alt, "#000000"  }, // infobar middle  selected
    [SchemeInfoNorm] = { col_gray3,      col_gray1,  "#000000"  }, // infobar middle  unselected
};
```
