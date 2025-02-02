#pragma once

enum class MaterialType : unsigned int{
    Air                      = 0x0,
    Dirt                     = 0x1,
    Wood                     = 0x2,
    Stone                    = 0x3,
    Metal                    = 0x4,
    Water                    = 0x5,
    Lava                     = 0x6,
    Leaves                   = 0x7,
    Plant                    = 0x8,
    SolidPlant               = 0x9,
    Sponge                   = 0xA,
    Cloth                    = 0xB,
    Bed                      = 0xC,
    Fire                     = 0xD,
    Sand                     = 0xE,
    Decoration               = 0xF,
    Glass                    = 0x10,
    Explosive                = 0x11,
    Ice                      = 0x12,
    PackedIce                = 0x13,
    TopSnow                  = 0x14,
    Snow                     = 0x15,
    PowderSnow               = 0x16,
    Amethyst                 = 0x17,
    Cactus                   = 0x18,
    Clay                     = 0x19,
    Vegetable                = 0x1A,
    Portal                   = 0x1B,
    Cake                     = 0x1C,
    Web                      = 0x1D,
    RedstoneWire             = 0x1E,
    Carpet                   = 0x1F,
    BuildableGlass           = 0x20,
    Slime                    = 0x21,
    Piston                   = 0x22,
    Allow                    = 0x23,
    Deny                     = 0x24,
    Netherwart               = 0x25,
    StoneDecoration          = 0x26,
    Bubble                   = 0x27,
    Egg                      = 0x28,
    SoftEgg                  = 0x29,
    Barrier                  = 0x2A,
    Coral                    = 0x2B,
    DecorationSolid          = 0x2C,
    Dripstone                = 0x2D,
    ReinforcedStone          = 0x2E,
    Sculk                    = 0x2F,
    SculkVein                = 0x30,
    ClientRequestPlaceholder = 0x31,
    StructureVoid            = 0x32,
    Root                     = 0x33,
    SurfaceTypeTotal         = 0x34,
    Any                      = 0x35,
};