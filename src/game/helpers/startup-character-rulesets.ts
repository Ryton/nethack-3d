import type { NethackRuntimeVersion } from "../../runtime/types";
import {
  GENERATED_STARTUP_CHARACTER_RULESETS,
  GENERATED_STARTUP_RACE_OPTIONS,
  GENERATED_STARTUP_ROLE_OPTIONS,
} from "./startup-character-rulesets.generated";

export const allStartupRoleOptions = GENERATED_STARTUP_ROLE_OPTIONS;

export const allStartupRaceOptions = GENERATED_STARTUP_RACE_OPTIONS;

export const startupGenderOptions = ["male", "female"] as const;

export const startupAlignOptions = ["lawful", "neutral", "chaotic"] as const;

export type StartupRole = (typeof allStartupRoleOptions)[number];
export type StartupRace = (typeof allStartupRaceOptions)[number];
export type StartupGender = (typeof startupGenderOptions)[number];
export type StartupAlign = (typeof startupAlignOptions)[number];

export type StartupRoleConstraint = {
  races: readonly StartupRace[];
  genders: readonly StartupGender[];
  aligns: readonly StartupAlign[];
};

export type StartupRaceConstraint = {
  genders: readonly StartupGender[];
  aligns: readonly StartupAlign[];
};

export type StartupCharacterRuleset = {
  roles: readonly StartupRole[];
  races: readonly StartupRace[];
  roleConstraints: Readonly<Partial<Record<StartupRole, StartupRoleConstraint>>>;
  raceConstraints: Readonly<Partial<Record<StartupRace, StartupRaceConstraint>>>;
};

export const startupCharacterRulesets = GENERATED_STARTUP_CHARACTER_RULESETS satisfies Readonly<
  Record<NethackRuntimeVersion, StartupCharacterRuleset>
>;

export function getStartupCharacterRuleset(
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupCharacterRuleset {
  return startupCharacterRulesets[runtimeVersion] ?? startupCharacterRulesets["3.6.7"];
}
