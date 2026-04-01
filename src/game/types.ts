import * as THREE from "three";

import type { GlyphKind } from "./glyphs/types";

export type TileMap = Map<string, THREE.Mesh>;

export interface GlyphOverlay {
  texture: THREE.CanvasTexture | null;
  material: THREE.MeshBasicMaterial;
  baseColorHex: string;
  textureKey: string;
}

export type GlyphOverlayMap = Map<string, GlyphOverlay>;
export type TerrainSnapshot = {
  glyph: number;
  kind?: GlyphKind;
  char?: string;
  color?: number;
  tileIndex?: number;
  symidx?: number;
  glyphFlags?: number;
};
