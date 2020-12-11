

/*
 *
 */
#define KEYGRP(_g)					(((_g) & 0x0f) << 12)
#define KEY_MASK					0x03ff
#define KEYCAP						0x0400
#define KEYMOD						0x0800
#define KEYGRP_MAX					15

#define KEYINDICATOR_MAX			7

#define VKEYMODBIT					32

#define KEY_NOSYM_FLAG				0x40
#define KEY_DEAD_FLAG				0x80

struct extended_map {
	char				from;
	char				to;
};

/*
 * Used in "mods" table for defining keyboard modifiers
 */
#define KEYMOD_UP					0x00		/* if key is up */
#define KEYMOD_DOWN					0x40		/* if key is down */
#define KEYMOD_RELEASE				0x80		/* if key was released */
#define KEYMOD_PRESS				0xc0		/* if key was pressed */
#define KEYMODBIT_MASK				0x3f

#define KEYMOD_OR					0x00		/* logical or */
#define KEYMOD_AND					0x80		/* logical and */

/*
 * Codes used in COMPOSE table
 */
#define KEYCOMPOSE_CODE				0x0000
#define KEYCOMPOSE_TABLE			0x4000
#define KEYCOMPOSE_SIZE				0x3fff
#define KEYCOMPOSE_LAST				0x8000

/*
 * Keymap types used in .kbd files
 */
#define KEYMAP_NAME					0
#define KEYMAP_EXTENDED_MAP			1
#define KEYMAP_GROUPS				2
#define KEYMAP_KEYS					3
#define KEYMAP_MODIFIERS			4
#define KEYMAP_COMPOSE				5
#define KEYMAP_INDICATORS			6
#define KEYMAP_GEOMETRY				7

#define KEYMAP_MAGIC				0x2044424b

struct keymap_hdr {
	unsigned short					len;
	unsigned short					type;
};
