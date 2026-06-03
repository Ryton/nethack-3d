import type { NethackRuntimeVersion } from "../runtime/types";

// Adapted from horlogeislux/tileto370 (MIT):
// https://github.com/horlogeislux/tileto370
// Original mapping logic converts 3.6.x tile order into 3.7 layout.
// We use the inverse lookup direction needed at runtime: 3.7 tile index -> 3.6.7 tile index.

const NH_TILES_PER_ROW = 40;
const NH37_OUTPUT_ROWS = 58;
const STATUE_TILE_ID_OFFSET = 1082;

enum TileAlias {
  DisplacerBeast = -38,
  GoldBabyDragon = -143,
  GoldDragon = -153,
  GeneticEngineer = -212,
  GenericStrange = -394,
  GenericWeapon = -411,
  GenericArmor = -509,
  GenericRing = -546,
  GenericAmulet = -575,
  GenericTool = -592,
  GenericFood = -664,
  GenericPotion = -668,
  GenericScroll = -694,
  GenericSpellbook = -737,
  GenericWand = -780,
  GenericCoin = -807,
  GenericGem = -808,
  GenericLargeRock = -844,
  GenericIronBall = -846,
  GenericIronChain = -847,
  GenericVenom = -849,
  SilverMace = -450,
  CrystalHelmet = -471,
  GoldDragonScaleMail = -485,
  GoldDragonScales = -495,
  PerforatedAmulet = -578,
  CubicalAmulet = -574,
  CheckeredSpellbook = -741,
  EngravingInRoom = -869,
  EngravingInCorridor = -872,
  BranchStaircaseUp = -873,
  BranchStaircaseDown = -874,
  BranchLadderUp = -875,
  BranchLadderDown = -876,
  Altar = -877,
  WallOfLava = -884,
  TrappedDoor = -866,
  DisplacerBeastStatue = DisplacerBeast - STATUE_TILE_ID_OFFSET,
  GoldBabyDragonStatue = GoldBabyDragon - STATUE_TILE_ID_OFFSET,
  GoldDragonStatue = GoldDragon - STATUE_TILE_ID_OFFSET,
  GeneticEngineerStatue = GeneticEngineer - STATUE_TILE_ID_OFFSET,
}

function duplicateRange(start: number, stop: number): number[] {
  const duplicated: number[] = [];
  for (let value = start; value < stop; value += 1) {
    duplicated.push(value, value);
  }
  return duplicated;
}

function indexRange(start: number, stop: number): number[] {
  const indexes: number[] = [];
  for (let value = start; value < stop; value += 1) {
    indexes.push(value);
  }
  return indexes;
}

function buildNh367TileIndexByNh37TileIndex(): ReadonlyArray<number> {
  return [
    ...duplicateRange(0, 41),
    ...[TileAlias.DisplacerBeast, TileAlias.DisplacerBeast],
    ...duplicateRange(41, 135),
    ...[TileAlias.GoldBabyDragon, TileAlias.GoldBabyDragon],
    ...duplicateRange(135, 145),
    ...[TileAlias.GoldDragon, TileAlias.GoldDragon],
    ...duplicateRange(145, 213),
    ...[TileAlias.GeneticEngineer, TileAlias.GeneticEngineer],
    ...duplicateRange(213, 293),
    295,
    293,
    294,
    294,
    ...duplicateRange(296, 337),
    337,
    338,
    ...duplicateRange(339, 342),
    342,
    343,
    ...duplicateRange(344, 393),
    393,
    394,
    TileAlias.GenericStrange,
    TileAlias.GenericWeapon,
    TileAlias.GenericArmor,
    TileAlias.GenericRing,
    TileAlias.GenericAmulet,
    TileAlias.GenericTool,
    TileAlias.GenericFood,
    TileAlias.GenericPotion,
    TileAlias.GenericScroll,
    TileAlias.GenericSpellbook,
    TileAlias.GenericWand,
    TileAlias.GenericCoin,
    TileAlias.GenericGem,
    TileAlias.GenericLargeRock,
    TileAlias.GenericIronBall,
    TileAlias.GenericIronChain,
    TileAlias.GenericVenom,
    ...indexRange(395, 451),
    TileAlias.SilverMace,
    ...indexRange(451, 472),
    TileAlias.CrystalHelmet,
    ...indexRange(472, 477),
    TileAlias.GoldDragonScaleMail,
    ...indexRange(477, 487),
    TileAlias.GoldDragonScales,
    ...indexRange(487, 583),
    TileAlias.PerforatedAmulet,
    TileAlias.CubicalAmulet,
    ...indexRange(583, 777),
    TileAlias.CheckeredSpellbook,
    ...indexRange(777, 871),
    TileAlias.EngravingInRoom,
    871,
    872,
    TileAlias.EngravingInCorridor,
    873,
    874,
    875,
    876,
    TileAlias.BranchStaircaseUp,
    TileAlias.BranchStaircaseDown,
    TileAlias.BranchLadderUp,
    TileAlias.BranchLadderDown,
    ...[TileAlias.Altar, TileAlias.Altar, TileAlias.Altar, TileAlias.Altar],
    ...indexRange(877, 885),
    TileAlias.WallOfLava,
    ...indexRange(885, 915),
    TileAlias.TrappedDoor,
    TileAlias.GenericStrange,
    ...indexRange(1000, 1032),
    ...indexRange(919, 1000),
    ...indexRange(1032, 1038),
    850,
    850,
    ...indexRange(1038, 1082),
    ...duplicateRange(1082, 1123),
    ...[TileAlias.DisplacerBeastStatue, TileAlias.DisplacerBeastStatue],
    ...duplicateRange(1123, 1217),
    ...[TileAlias.GoldBabyDragonStatue, TileAlias.GoldBabyDragonStatue],
    ...duplicateRange(1217, 1227),
    ...[TileAlias.GoldDragonStatue, TileAlias.GoldDragonStatue],
    ...duplicateRange(1227, 1295),
    ...[TileAlias.GeneticEngineerStatue, TileAlias.GeneticEngineerStatue],
    ...duplicateRange(1295, 1375),
    1377,
    1375,
    1376,
    1376,
    ...duplicateRange(1378, 1419),
    1419,
    1420,
    ...duplicateRange(1421, 1424),
    1424,
    1425,
    ...duplicateRange(1426, 1475),
    1475,
    ...Array.from({ length: 20 }, () => 1476),
  ];
}

const NH367_TILE_INDEX_BY_NH37_TILE_INDEX = buildNh367TileIndexByNh37TileIndex();
const NH37_TILE_INDEX_BY_NH367_TILE_INDEX = new Map<number, number>();
for (
  let nh37TileIndex = 0;
  nh37TileIndex < NH367_TILE_INDEX_BY_NH37_TILE_INDEX.length;
  nh37TileIndex += 1
) {
  const rawMappedTileIndex = NH367_TILE_INDEX_BY_NH37_TILE_INDEX[nh37TileIndex];
  const normalizedMappedTileIndex =
    rawMappedTileIndex < 0
      ? Math.abs(rawMappedTileIndex)
      : Math.trunc(rawMappedTileIndex);
  if (!Number.isFinite(normalizedMappedTileIndex) || normalizedMappedTileIndex < 0) {
    continue;
  }
  if (!NH37_TILE_INDEX_BY_NH367_TILE_INDEX.has(normalizedMappedTileIndex)) {
    NH37_TILE_INDEX_BY_NH367_TILE_INDEX.set(
      normalizedMappedTileIndex,
      nh37TileIndex,
    );
  }
}

export const nh37TilesPerRow = NH_TILES_PER_ROW;
export const nh37OutputRows = NH37_OUTPUT_ROWS;
export const nh37ExpectedTileCount =
  NH_TILES_PER_ROW * NH37_OUTPUT_ROWS;

export function shouldTranslateNh367TilesetForNh37Runtime(
  runtimeVersion: NethackRuntimeVersion,
  atlasTileCount: number,
  tileLayoutVersion:
    | "slashem"
    | "3.4.3"
    | "3.6.7"
    | "3.7"
    | "evilhack"
    | "unknown" = "unknown",
): boolean {
  if (runtimeVersion !== "3.7") {
    return false;
  }
  if (
    tileLayoutVersion === "3.7" ||
    tileLayoutVersion === "slashem" ||
    tileLayoutVersion === "3.4.3"
  ) {
    return false;
  }
  const normalizedAtlasTileCount = Math.max(0, Math.trunc(atlasTileCount));
  return (
    normalizedAtlasTileCount > 0 &&
    normalizedAtlasTileCount < nh37ExpectedTileCount
  );
}

export function translateNh37TileIndexToNh367(
  tileIndex: number,
): number {
  const normalizedTileIndex = Math.trunc(tileIndex);
  if (!Number.isFinite(normalizedTileIndex) || normalizedTileIndex < 0) {
    return normalizedTileIndex;
  }
  const mappedTileIndex =
    NH367_TILE_INDEX_BY_NH37_TILE_INDEX[normalizedTileIndex];
  if (!Number.isFinite(mappedTileIndex)) {
    return normalizedTileIndex;
  }
  return mappedTileIndex < 0
    ? Math.abs(mappedTileIndex)
    : Math.trunc(mappedTileIndex);
}

export function translateNh37TileIndexToNh367PreservingAliases(
  tileIndex: number,
): number {
  const normalizedTileIndex = Math.trunc(tileIndex);
  if (!Number.isFinite(normalizedTileIndex) || normalizedTileIndex < 0) {
    return normalizedTileIndex;
  }
  const mappedTileIndex =
    NH367_TILE_INDEX_BY_NH37_TILE_INDEX[normalizedTileIndex];
  if (!Number.isFinite(mappedTileIndex)) {
    return normalizedTileIndex;
  }
  return Math.trunc(mappedTileIndex);
}

export function translateNh367TileIndexToNh37(
  tileIndex: number,
): number {
  const normalizedTileIndex = Math.trunc(tileIndex);
  if (!Number.isFinite(normalizedTileIndex) || normalizedTileIndex < 0) {
    return normalizedTileIndex;
  }
  const shiftedTileIndex =
    NH37_TILE_INDEX_BY_NH367_TILE_INDEX.get(normalizedTileIndex);
  if (typeof shiftedTileIndex !== "number" || !Number.isFinite(shiftedTileIndex)) {
    return normalizedTileIndex;
  }
  return Math.trunc(shiftedTileIndex);
}
