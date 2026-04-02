import type { NethackRuntimeVersion } from "../../runtime/types";
import {
  getStartupCharacterRuleset,
  startupAlignOptions,
  startupGenderOptions,
  type StartupAlign,
  type StartupGender,
  type StartupRace,
  type StartupRole,
} from "./startup-character-rulesets";

export type StartupCreateCharacterSelection = {
  role: StartupRole;
  race: StartupRace;
  gender: StartupGender;
  align: StartupAlign;
};

export type StartupCreateCharacterOptionSet = {
  roleOptions: readonly StartupRole[];
  raceOptions: StartupRace[];
  genderOptions: StartupGender[];
  alignOptions: StartupAlign[];
  selection: StartupCreateCharacterSelection;
};

function normalizeOption<T extends string>(
  value: unknown,
  allowedValues: readonly T[],
  fallbackValue: T,
): T {
  const normalized = String(value || "")
    .trim()
    .toLowerCase();
  if (normalized) {
    const matchedValue = allowedValues.find(
      (candidate) => candidate.toLowerCase() === normalized,
    );
    if (matchedValue) {
      return matchedValue;
    }
  }
  return fallbackValue;
}

function intersectAllowedValues<T extends string>(
  preferredOrder: readonly T[],
  ...allowedGroups: readonly (readonly T[])[]
): T[] {
  if (allowedGroups.length === 0) {
    return [...preferredOrder];
  }
  return preferredOrder.filter((candidate) =>
    allowedGroups.every((group) => group.includes(candidate)),
  );
}

function pickRandomItem<T>(
  options: readonly T[],
  fallback: T,
): T {
  if (options.length === 0) {
    return fallback;
  }
  const randomIndex = Math.floor(Math.random() * options.length);
  return options[randomIndex] ?? fallback;
}

export function resolveStartupCreateCharacterOptionSet(
  rawSelection: {
    role?: unknown;
    race?: unknown;
    gender?: unknown;
    align?: unknown;
  },
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupCreateCharacterOptionSet {
  const ruleset = getStartupCharacterRuleset(runtimeVersion);
  const defaultRole = ruleset.roles[0] ?? "Archeologist";
  const role = normalizeOption(rawSelection.role, ruleset.roles, defaultRole);
  const roleConstraint =
    ruleset.roleConstraints[role] ?? ruleset.roleConstraints[defaultRole];

  const raceOptions = roleConstraint?.races ? [...roleConstraint.races] : [];
  const defaultRace = raceOptions[0] ?? ruleset.races[0] ?? "human";
  const race = normalizeOption(rawSelection.race, raceOptions, defaultRace);

  const raceConstraint = ruleset.raceConstraints[race];
  const raceGenders = raceConstraint?.genders ?? startupGenderOptions;
  const genderOptions = intersectAllowedValues(
    startupGenderOptions,
    roleConstraint?.genders ?? startupGenderOptions,
    raceGenders,
  );
  const defaultGender = genderOptions[0] ?? startupGenderOptions[0] ?? "male";
  const gender = normalizeOption(rawSelection.gender, genderOptions, defaultGender);

  const raceAligns = raceConstraint?.aligns ?? startupAlignOptions;
  const alignOptions = intersectAllowedValues(
    startupAlignOptions,
    roleConstraint?.aligns ?? startupAlignOptions,
    raceAligns,
  );
  const defaultAlign = alignOptions[0] ?? startupAlignOptions[0] ?? "lawful";
  const align = normalizeOption(rawSelection.align, alignOptions, defaultAlign);

  return {
    roleOptions: ruleset.roles,
    raceOptions,
    genderOptions,
    alignOptions,
    selection: {
      role,
      race,
      gender,
      align,
    },
  };
}

export function normalizeStartupCreateCharacterSelection(
  rawSelection: {
    role?: unknown;
    race?: unknown;
    gender?: unknown;
    align?: unknown;
  },
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupCreateCharacterSelection {
  return resolveStartupCreateCharacterOptionSet(rawSelection, runtimeVersion).selection;
}

export function pickRandomStartupRole(
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupRole {
  const ruleset = getStartupCharacterRuleset(runtimeVersion);
  return pickRandomItem(ruleset.roles, ruleset.roles[0] ?? "Archeologist");
}

export function pickRandomStartupGenderForRole(
  role: unknown,
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupGender {
  const optionSet = resolveStartupCreateCharacterOptionSet(
    { role },
    runtimeVersion,
  );
  return pickRandomItem(
    optionSet.genderOptions,
    startupGenderOptions[0] ?? "male",
  );
}

export function pickRandomStartupCreateCharacterSelection(
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupCreateCharacterSelection {
  const defaultSelection = normalizeStartupCreateCharacterSelection(
    {},
    runtimeVersion,
  );
  const role = pickRandomStartupRole(runtimeVersion);
  const roleOptionSet = resolveStartupCreateCharacterOptionSet(
    { role },
    runtimeVersion,
  );
  const race = pickRandomItem(
    roleOptionSet.raceOptions,
    roleOptionSet.selection.race,
  );
  const raceOptionSet = resolveStartupCreateCharacterOptionSet(
    { role, race },
    runtimeVersion,
  );
  const gender = pickRandomItem(
    raceOptionSet.genderOptions,
    raceOptionSet.selection.gender,
  );
  const align = pickRandomItem(
    raceOptionSet.alignOptions,
    raceOptionSet.selection.align,
  );
  return normalizeStartupCreateCharacterSelection(
    {
      role: role || defaultSelection.role,
      race: race || defaultSelection.race,
      gender: gender || defaultSelection.gender,
      align: align || defaultSelection.align,
    },
    runtimeVersion,
  );
}
