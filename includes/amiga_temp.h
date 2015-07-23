#ifndef __AMIGA_TEMP_H__
#define __AMIGA_TEMP_H__

#include "types.h"

struct AreaInfo
{
    WORD   *VctrTbl;	     /* ptr to start of vector table */
    WORD   *VctrPtr;	     /* ptr to current vertex */
    BYTE    *FlagTbl;	      /* ptr to start of vector flag table */
    BYTE    *FlagPtr;	      /* ptrs to areafill flags */
    WORD   Count;	     /* number of vertices in list */
    WORD   MaxCount;	     /* AreaMove/Draw will not allow Count>MaxCount*/
    WORD   FirstX, FirstY;    /* first point for this polygon */
};

struct TmpRas
{
    BYTE *RasPtr;
    LONG Size;
};

/* unoptimized for 32bit alignment of pointers */
struct GelsInfo
{
    BYTE sprRsrvd;	      /* flag of which sprites to reserve from
                          vsprite system */
    UBYTE Flags;	      /* system use */
    struct VSprite *gelHead, *gelTail; /* dummy vSprites for list management*/
    /* pointer to array of 8 WORDS for sprite available lines */
    WORD *nextLine;
    /* pointer to array of 8 pointers for color-last-assigned to vSprites */
    WORD **lastColor;
    struct collTable *collHandler;     /* addresses of collision routines */
    WORD leftmost, rightmost, topmost, bottommost;
    APTR firstBlissObj, lastBlissObj;    /* system use only */
};

struct RastPort
{
    struct  Layer *Layer;
    struct  BitMap   *BitMap;
    UWORD  *AreaPtrn;	     /* ptr to areafill pattern */
    struct  TmpRas *TmpRas;
    struct  AreaInfo *AreaInfo;
    struct  GelsInfo *GelsInfo;
    UBYTE   Mask;	      /* write mask for this raster */
    BYTE    FgPen;	      /* foreground pen for this raster */
    BYTE    BgPen;	      /* background pen  */
    BYTE    AOlPen;	      /* areafill outline pen */
    BYTE    DrawMode;	      /* drawing mode for fill, lines, and text */
    BYTE    AreaPtSz;	      /* 2^n words for areafill pattern */
    BYTE    linpatcnt;	      /* current line drawing pattern preshift */
    BYTE    dummy;
    UWORD  Flags;	     /* miscellaneous control bits */
    UWORD  LinePtrn;	     /* 16 bits for textured lines */
    WORD   cp_x, cp_y;	     /* current pen position */
    UBYTE   minterms[ 8 ];
    WORD   PenWidth;
    WORD   PenHeight;
    struct  TextFont *Font;   /* current font address */
    UBYTE   AlgoStyle;	      /* the algorithmically generated style */
    UBYTE   TxFlags;	      /* text specific flags */
    UWORD   TxHeight;	      /* text height */
    UWORD   TxWidth;	      /* text nominal width */
    UWORD   TxBaseline;       /* text baseline */
    WORD    TxSpacing;	      /* text spacing (per character) */
    APTR    *RP_User;
    ULONG   longreserved[ 2 ];
#ifndef GFX_RASTPORT_1_2
    UWORD   wordreserved[ 7 ];  /* used to be a node */
    UBYTE   reserved[ 8 ];      /* for future use */
#endif
};

/* drawing modes */
#define JAM1	    0	      /* jam 1 color into raster */
#define JAM2	    1	      /* jam 2 colors into raster */
#define COMPLEMENT  2	      /* XOR bits into raster */
#define INVERSVID   4	      /* inverse video for drawing modes */

/* these are the flag bits for RastPort flags */
#define FRST_DOT    0x01      /* draw the first dot of this line ? */
#define ONE_DOT     0x02      /* use one dot mode for drawing lines */
#define DBUFFER     0x04      /* flag set when RastPorts
are double-buffered */

/* only used for bobs */

#define AREAOUTLINE 0x08      /* used by areafiller */
#define NOCROSSFILL 0x20      /* areafills have no crossovers */

/* there is only one style of clipping: raster clipping */
/* this preserves the continuity of jaggies regardless of clip window */
/* When drawing into a RastPort, if the ptr to ClipRect is nil then there */
/* is no clipping done, this is dangerous but useful for speed */

/* Shit I put in here*/
struct TmpRas
{
    BYTE *RasPtr;
    LONG Size;
};

struct BitMap
{
    UWORD   BytesPerRow;
    UWORD   Rows;
    UBYTE   Flags;
    UBYTE   Depth;
    UWORD   pad;
    PLANEPTR Planes[ 8 ];
};

struct RastPort
{
    struct  Layer *Layer;
    struct  BitMap   *BitMap;
    UWORD  *AreaPtrn;	     /* ptr to areafill pattern */
    struct  TmpRas *TmpRas;
    struct  AreaInfo *AreaInfo;
    struct  GelsInfo *GelsInfo;
    UBYTE   Mask;	      /* write mask for this raster */
    BYTE    FgPen;	      /* foreground pen for this raster */
    BYTE    BgPen;	      /* background pen  */
    BYTE    AOlPen;	      /* areafill outline pen */
    BYTE    DrawMode;	      /* drawing mode for fill, lines, and text */
    BYTE    AreaPtSz;	      /* 2^n words for areafill pattern */
    BYTE    linpatcnt;	      /* current line drawing pattern preshift */
    BYTE    dummy;
    UWORD  Flags;	     /* miscellaneous control bits */
    UWORD  LinePtrn;	     /* 16 bits for textured lines */
    WORD   cp_x, cp_y;	     /* current pen position */
    UBYTE   minterms[ 8 ];
    WORD   PenWidth;
    WORD   PenHeight;
    struct  TextFont *Font;   /* current font address */
    UBYTE   AlgoStyle;	      /* the algorithmically generated style */
    UBYTE   TxFlags;	      /* text specific flags */
    UWORD   TxHeight;	      /* text height */
    UWORD   TxWidth;	      /* text nominal width */
    UWORD   TxBaseline;       /* text baseline */
    WORD    TxSpacing;	      /* text spacing (per character) */
    APTR    *RP_User;
    ULONG   longreserved[ 2 ];
#ifndef GFX_RASTPORT_1_2
    UWORD   wordreserved[ 7 ];  /* used to be a node */
    UBYTE   reserved[ 8 ];      /* for future use */
#endif
};

struct TextAttr
{
    STRPTR  ta_Name;		/* name of the font */
    UWORD   ta_YSize;		/* height of the font */
    UBYTE   ta_Style;		/* intrinsic font style */
    UBYTE   ta_Flags;		/* font preferences and flags */
};

/*------ Font Styles ------------------------------------------------*/
#define	FS_NORMAL	0	/* normal text (no style bits set) */
#define	FSB_UNDERLINED	0	/* underlined (under baseline) */
#define	FSF_UNDERLINED	0x01
#define	FSB_BOLD	1	/* bold face text (ORed w/ shifted) */
#define	FSF_BOLD	0x02
#define	FSB_ITALIC	2	/* italic (slanted 1:2 right) */
#define	FSF_ITALIC	0x04
#define	FSB_EXTENDED	3	/* extended face (wider than normal) */
#define	FSF_EXTENDED	0x08

#define	FSB_COLORFONT	6	/* this uses ColorTextFont structure */
#define	FSF_COLORFONT	0x40
#define	FSB_TAGGED	7	/* the TextAttr is really an TTextAttr, */
#define	FSF_TAGGED	0x80

/*------ Font Flags -------------------------------------------------*/
#define	FPB_ROMFONT	0	/* font is in rom */
#define	FPF_ROMFONT	0x01
#define	FPB_DISKFONT	1	/* font is from diskfont.library */
#define	FPF_DISKFONT	0x02
#define	FPB_REVPATH	2	/* designed path is reversed (e.g. left) */
#define	FPF_REVPATH	0x04
#define	FPB_TALLDOT	3	/* designed for hires non-interlaced */
#define	FPF_TALLDOT	0x08
#define	FPB_WIDEDOT	4	/* designed for lores interlaced */
#define	FPF_WIDEDOT	0x10
#define	FPB_PROPORTIONAL 5	/* character sizes can vary from nominal */
#define	FPF_PROPORTIONAL 0x20
#define	FPB_DESIGNED	6	/* size explicitly designed, not constructed */
/* note: if you do not set this bit in your */
/* textattr, then a font may be constructed */
/* for you by scaling an existing rom or disk */
/* font (under V36 and above). */
#define	FPF_DESIGNED	0x40
/* bit 7 is always clear for fonts on the graphics font list */
#define	FPB_REMOVED	7	/* the font has been removed */
#define	FPF_REMOVED	(1<<7)


#endif