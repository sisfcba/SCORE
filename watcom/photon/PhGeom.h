
#ifndef _PH_GEOM_H
#define _PH_GEOM_H

struct Ph_point { short x, y; };
struct Ph_dim { unsigned short w, h; };
struct Ph_lpoint { long x, y; };
struct Ph_rgb { unsigned short r, g, b; };
// struct Ph_prect { PhPoint_t ul, lr; };		
struct Ph_rect { struct Ph_point ul, lr; };
struct Ph_area { struct Ph_point pos;
                 struct Ph_dim size; };
struct Ph_extent { struct Ph_rect rect;
                   unsigned short valid; };

//  Support for the old-style rectangle/area definitions
struct Ph_rectold { short xUL, yUL, xLR, yLR; };
struct Ph_areaold { short x, y, w, h; };
struct Ph_extentold { short xUL, yUL, xLR, yLR, valid; };
             

//  Graphics specific add-ons.
struct Ph_span   { short x1, x2, y; };
struct Ph_2short { short a, b; };
struct Ph_transMat {
	struct Ph_lpoint		xm, ym;
	struct Ph_point			xlat;
	unsigned			flags;
};
struct Ph_rgb_bytes { unsigned short r, g, b; };



// Renderlib specific add-ons...
struct Ph_areahw {
	short x;
	short y;
	short w;
	short h;
};

#endif   //  _PH_GEOM_H

