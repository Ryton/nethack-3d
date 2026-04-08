export const FPS_HELD_WEAPON_MELEE_SWIPE_ANIMATION_ID = "melee_swipe";
export const FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_2_ANIMATION_ID =
  "melee_swipe_2";
export const FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_3_ANIMATION_ID =
  "melee_swipe_3";
export const FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_4_ANIMATION_ID =
  "melee_swipe_4";
export const FPS_HELD_WEAPON_MELEE_SWIPE_ANIMATION_IDS = [
  FPS_HELD_WEAPON_MELEE_SWIPE_ANIMATION_ID,
  FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_2_ANIMATION_ID,
  FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_3_ANIMATION_ID,
  FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_4_ANIMATION_ID,
] as const;

export type FpsHeldWeaponAnimationVector3 = {
  x: number;
  y: number;
  z: number;
};

export type FpsHeldWeaponAnimationSoundEffect = "missed_attack";

export type FpsHeldWeaponAnimationKeyframe = {
  durationMs: number;
  translation: FpsHeldWeaponAnimationVector3;
  rotationDeg: FpsHeldWeaponAnimationVector3;
  soundEffect?: FpsHeldWeaponAnimationSoundEffect;
};

export type FpsHeldWeaponAnimationDefinition = {
  id: string;
  label: string;
  weight: number;
  pivotNormalized: FpsHeldWeaponAnimationVector3;
  keyframes: FpsHeldWeaponAnimationKeyframe[];
};

export type FpsHeldWeaponAnimationLibrary = Record<
  string,
  FpsHeldWeaponAnimationDefinition
>;

export type FpsHeldWeaponAnimationSample = {
  active: boolean;
  complete: boolean;
  currentKeyframeIndex: number | null;
  translation: FpsHeldWeaponAnimationVector3;
  rotationDeg: FpsHeldWeaponAnimationVector3;
};

const createZeroVector3 = (): FpsHeldWeaponAnimationVector3 => ({
  x: 0,
  y: 0,
  z: 0,
});

const clampDurationMs = (value: number): number =>
  Math.max(1, Math.round(Number.isFinite(value) ? value : 1));

const sanitizeNumber = (value: number, fallback: number = 0): number =>
  Number.isFinite(value) ? value : fallback;

const clampAnimationWeight = (value: number): number =>
  Math.max(0, sanitizeNumber(value, 1));

const cloneVector3 = (
  value: FpsHeldWeaponAnimationVector3 | null | undefined,
): FpsHeldWeaponAnimationVector3 => ({
  x: sanitizeNumber(value?.x ?? 0),
  y: sanitizeNumber(value?.y ?? 0),
  z: sanitizeNumber(value?.z ?? 0),
});

const cloneKeyframe = (
  keyframe: FpsHeldWeaponAnimationKeyframe | null | undefined,
): FpsHeldWeaponAnimationKeyframe => ({
  durationMs: clampDurationMs(keyframe?.durationMs ?? 100),
  translation: cloneVector3(keyframe?.translation),
  rotationDeg: cloneVector3(keyframe?.rotationDeg),
  soundEffect:
    keyframe?.soundEffect === "missed_attack"
      ? keyframe.soundEffect
      : undefined,
});

const createDefaultKeyframe = (): FpsHeldWeaponAnimationKeyframe => ({
  durationMs: 100,
  translation: createZeroVector3(),
  rotationDeg: createZeroVector3(),
});

const createDefaultMeleeSwipe1Keyframes =
  (): FpsHeldWeaponAnimationKeyframe[] => [
    {
      durationMs: 1,
      translation: {
        x: -0.23,
        y: 0.16,
        z: -0.07,
      },
      rotationDeg: {
        x: -85.9,
        y: -29.4,
        z: -131,
      },
      soundEffect: "missed_attack",
    },
    {
      durationMs: 170,
      translation: {
        x: -1.15,
        y: 0.25,
        z: 0.16,
      },
      rotationDeg: {
        x: -68.2,
        y: 0,
        z: 67.1,
      },
    },
    {
      durationMs: 400,
      translation: {
        x: -0.401,
        y: -0.026,
        z: 0.055,
      },
      rotationDeg: {
        x: -8.2,
        y: 0,
        z: -65.4,
      },
    },
  ];

const createDefaultMeleeSwipe2Keyframes =
  (): FpsHeldWeaponAnimationKeyframe[] => [
    {
      durationMs: 1,
      translation: {
        x: -0.96,
        y: 0.14,
        z: -0.07,
      },
      rotationDeg: {
        x: -94.5,
        y: 34.5,
        z: 71.1,
      },
      soundEffect: "missed_attack",
    },
    {
      durationMs: 200,
      translation: {
        x: -0.12,
        y: 0,
        z: 0,
      },
      rotationDeg: {
        x: -53.8,
        y: -1.2,
        z: -145.7,
      },
    },
    {
      durationMs: 350,
      translation: {
        x: -0.401,
        y: -0.026,
        z: 0.055,
      },
      rotationDeg: {
        x: -8.2,
        y: 0,
        z: -65.4,
      },
    },
  ];

const createDefaultMeleeSwipe3Keyframes =
  (): FpsHeldWeaponAnimationKeyframe[] => [
    {
      durationMs: 1,
      translation: {
        x: -0.3,
        y: 0.44,
        z: 0,
      },
      rotationDeg: {
        x: 0,
        y: -100,
        z: -60,
      },
      soundEffect: "missed_attack",
    },
    {
      durationMs: 110,
      translation: {
        x: -0.34,
        y: 0.08,
        z: 0,
      },
      rotationDeg: {
        x: 0.4,
        y: -75.2,
        z: 70,
      },
    },
    {
      durationMs: 400,
      translation: {
        x: -0.401,
        y: -0.026,
        z: 0.055,
      },
      rotationDeg: {
        x: -8.2,
        y: 0,
        z: -65.4,
      },
    },
  ];

const createDefaultMeleeSwipe4Keyframes =
  (): FpsHeldWeaponAnimationKeyframe[] => [
    {
      durationMs: 1,
      translation: {
        x: -0.49,
        y: 0.3,
        z: 0.5,
      },
      rotationDeg: {
        x: -102.9,
        y: -29.7,
        z: -49.4,
      },
      soundEffect: "missed_attack",
    },
    {
      durationMs: 75,
      translation: {
        x: -0.5,
        y: 0.37,
        z: 0.05,
      },
      rotationDeg: {
        x: -93.5,
        y: -34.2,
        z: -37.4,
      },
    },
    {
      durationMs: 400,
      translation: {
        x: -0.401,
        y: -0.026,
        z: 0.055,
      },
      rotationDeg: {
        x: -8.2,
        y: 0,
        z: -65.4,
      },
    },
  ];

export const defaultFpsHeldWeaponAnimationLibrary: FpsHeldWeaponAnimationLibrary =
  {
    [FPS_HELD_WEAPON_MELEE_SWIPE_ANIMATION_ID]: {
      id: FPS_HELD_WEAPON_MELEE_SWIPE_ANIMATION_ID,
      label: "Melee Swipe 1",
      weight: 1,
      pivotNormalized: {
        x: 0.46,
        y: -0.5,
        z: 0,
      },
      keyframes: createDefaultMeleeSwipe1Keyframes(),
    },
    [FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_2_ANIMATION_ID]: {
      id: FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_2_ANIMATION_ID,
      label: "Melee Swipe 2",
      weight: 1,
      pivotNormalized: {
        x: 0.46,
        y: -0.5,
        z: 0,
      },
      keyframes: createDefaultMeleeSwipe2Keyframes(),
    },
    [FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_3_ANIMATION_ID]: {
      id: FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_3_ANIMATION_ID,
      label: "Melee Swipe 3",
      weight: 0.5,
      pivotNormalized: {
        x: 0.46,
        y: -0.5,
        z: 0,
      },
      keyframes: createDefaultMeleeSwipe3Keyframes(),
    },
    [FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_4_ANIMATION_ID]: {
      id: FPS_HELD_WEAPON_MELEE_SWIPE_VARIATION_4_ANIMATION_ID,
      label: "Melee Swipe 4",
      weight: 0.5,
      pivotNormalized: {
        x: 0.46,
        y: -0.5,
        z: 0,
      },
      keyframes: createDefaultMeleeSwipe4Keyframes(),
    },
  };

export const cloneFpsHeldWeaponAnimationDefinition = (
  animation: FpsHeldWeaponAnimationDefinition,
): FpsHeldWeaponAnimationDefinition => ({
  id: animation.id,
  label: animation.label,
  weight: clampAnimationWeight(animation.weight),
  pivotNormalized: cloneVector3(animation.pivotNormalized),
  keyframes:
    animation.keyframes.length > 0
      ? animation.keyframes.map((keyframe) => cloneKeyframe(keyframe))
      : [createDefaultKeyframe()],
});

export const cloneFpsHeldWeaponAnimationLibrary = (
  library: FpsHeldWeaponAnimationLibrary,
): FpsHeldWeaponAnimationLibrary => {
  const cloned: FpsHeldWeaponAnimationLibrary = {};
  for (const [id, animation] of Object.entries(library)) {
    cloned[id] = cloneFpsHeldWeaponAnimationDefinition(animation);
  }
  return cloned;
};

export const createDefaultFpsHeldWeaponAnimationLibrary =
  (): FpsHeldWeaponAnimationLibrary =>
    cloneFpsHeldWeaponAnimationLibrary(defaultFpsHeldWeaponAnimationLibrary);

export const getFpsHeldWeaponAnimationTotalDurationMs = (
  animation: FpsHeldWeaponAnimationDefinition | null | undefined,
  durationScale: number = 1,
): number => {
  if (!animation) {
    return 0;
  }
  const normalizedDurationScale =
    Number.isFinite(durationScale) && durationScale > 0 ? durationScale : 1;
  return animation.keyframes.reduce(
    (total, keyframe) =>
      total + clampDurationMs(keyframe.durationMs) * normalizedDurationScale,
    0,
  );
};

const smoothstep01 = (value: number): number => {
  const t = Math.min(1, Math.max(0, value));
  return t * t * (3 - 2 * t);
};

const lerpNumber = (start: number, end: number, t: number): number =>
  start + (end - start) * t;

const lerpVector3 = (
  from: FpsHeldWeaponAnimationVector3,
  to: FpsHeldWeaponAnimationVector3,
  t: number,
): FpsHeldWeaponAnimationVector3 => ({
  x: lerpNumber(from.x, to.x, t),
  y: lerpNumber(from.y, to.y, t),
  z: lerpNumber(from.z, to.z, t),
});

export const sampleFpsHeldWeaponAnimation = (
  animation: FpsHeldWeaponAnimationDefinition | null | undefined,
  elapsedMs: number,
  durationScale: number = 1,
): FpsHeldWeaponAnimationSample => {
  if (!animation || animation.keyframes.length <= 0) {
    return {
      active: false,
      complete: true,
      currentKeyframeIndex: null,
      translation: createZeroVector3(),
      rotationDeg: createZeroVector3(),
    };
  }

  const normalizedElapsedMs = Math.max(0, sanitizeNumber(elapsedMs, 0));
  const normalizedDurationScale =
    Number.isFinite(durationScale) && durationScale > 0 ? durationScale : 1;
  const totalDurationMs = getFpsHeldWeaponAnimationTotalDurationMs(
    animation,
    normalizedDurationScale,
  );
  const lastKeyframe = animation.keyframes[animation.keyframes.length - 1];
  if (normalizedElapsedMs >= totalDurationMs) {
    return {
      active: false,
      complete: true,
      currentKeyframeIndex: animation.keyframes.length - 1,
      translation: cloneVector3(lastKeyframe.translation),
      rotationDeg: cloneVector3(lastKeyframe.rotationDeg),
    };
  }

  let segmentStartMs = 0;
  let previousTranslation = createZeroVector3();
  let previousRotationDeg = createZeroVector3();
  for (let index = 0; index < animation.keyframes.length; index += 1) {
    const keyframe = animation.keyframes[index];
    const segmentDurationMs =
      clampDurationMs(keyframe.durationMs) * normalizedDurationScale;
    const segmentEndMs = segmentStartMs + segmentDurationMs;
    if (normalizedElapsedMs < segmentEndMs) {
      const t = smoothstep01(
        segmentDurationMs > 0
          ? (normalizedElapsedMs - segmentStartMs) / segmentDurationMs
          : 1,
      );
      return {
        active: true,
        complete: false,
        currentKeyframeIndex: index,
        translation: lerpVector3(previousTranslation, keyframe.translation, t),
        rotationDeg: lerpVector3(previousRotationDeg, keyframe.rotationDeg, t),
      };
    }
    segmentStartMs = segmentEndMs;
    previousTranslation = keyframe.translation;
    previousRotationDeg = keyframe.rotationDeg;
  }

  return {
    active: false,
    complete: true,
    currentKeyframeIndex: animation.keyframes.length - 1,
    translation: cloneVector3(lastKeyframe.translation),
    rotationDeg: cloneVector3(lastKeyframe.rotationDeg),
  };
};

const roundNumber = (value: number, decimals: number): number => {
  const factor = 10 ** decimals;
  return Math.round(value * factor) / factor;
};

export const serializeFpsHeldWeaponAnimationDefinition = (
  animation: FpsHeldWeaponAnimationDefinition,
): string =>
  JSON.stringify(
    {
      id: animation.id,
      label: animation.label,
      weight: roundNumber(clampAnimationWeight(animation.weight), 4),
      pivotNormalized: {
        x: roundNumber(sanitizeNumber(animation.pivotNormalized.x), 4),
        y: roundNumber(sanitizeNumber(animation.pivotNormalized.y), 4),
        z: roundNumber(sanitizeNumber(animation.pivotNormalized.z), 4),
      },
      keyframes: animation.keyframes.map((keyframe) => ({
        durationMs: clampDurationMs(keyframe.durationMs),
        translation: {
          x: roundNumber(sanitizeNumber(keyframe.translation.x), 4),
          y: roundNumber(sanitizeNumber(keyframe.translation.y), 4),
          z: roundNumber(sanitizeNumber(keyframe.translation.z), 4),
        },
        rotationDeg: {
          x: roundNumber(sanitizeNumber(keyframe.rotationDeg.x), 4),
          y: roundNumber(sanitizeNumber(keyframe.rotationDeg.y), 4),
          z: roundNumber(sanitizeNumber(keyframe.rotationDeg.z), 4),
        },
        ...(keyframe.soundEffect
          ? {
              soundEffect: keyframe.soundEffect,
            }
          : {}),
      })),
    },
    null,
    2,
  );
