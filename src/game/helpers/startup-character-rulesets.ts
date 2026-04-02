import type { NethackRuntimeVersion } from "../../runtime/types";

export const allStartupRoleOptions = [
  "Archeologist",
  "Barbarian",
  "Caveman",
  "Flame Mage",
  "Healer",
  "Ice Mage",
  "Knight",
  "Monk",
  "Necromancer",
  "Priest",
  "Ranger",
  "Rogue",
  "Samurai",
  "Tourist",
  "Undead Slayer",
  "Valkyrie",
  "Wizard",
  "Yeoman",
] as const;

export const allStartupRaceOptions = [
  "doppelganger",
  "drow",
  "dwarf",
  "elf",
  "gnome",
  "hobbit",
  "human",
  "lycanthrope",
  "orc",
  "vampire",
] as const;

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

function defineStartupCharacterRuleset(
  ruleset: StartupCharacterRuleset,
): StartupCharacterRuleset {
  return ruleset;
}

const startup367Ruleset = defineStartupCharacterRuleset({
  // Source: \\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo\packages\wasm-367\NetHack\src\role.c
  roles: [
    "Archeologist",
    "Barbarian",
    "Caveman",
    "Healer",
    "Knight",
    "Monk",
    "Priest",
    "Rogue",
    "Ranger",
    "Samurai",
    "Tourist",
    "Valkyrie",
    "Wizard",
  ],
  races: ["human", "elf", "dwarf", "gnome", "orc"],
  roleConstraints: {
    Archeologist: {
      races: ["human", "dwarf", "gnome"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    Barbarian: {
      races: ["human", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Caveman: {
      races: ["human", "dwarf", "gnome"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    Healer: {
      races: ["human", "gnome"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    Knight: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Monk: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Priest: {
      races: ["human", "elf"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Rogue: {
      races: ["human", "orc"],
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    Ranger: {
      races: ["human", "elf", "gnome", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Samurai: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Tourist: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    Valkyrie: {
      races: ["human", "dwarf"],
      genders: ["female"],
      aligns: ["lawful", "neutral"],
    },
    Wizard: {
      races: ["human", "elf", "gnome", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
  },
  raceConstraints: {
    human: {
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    elf: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    dwarf: {
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    gnome: {
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    orc: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
  },
});

const startup37Ruleset = defineStartupCharacterRuleset({
  // Source: \\wsl.localhost\Ubuntu\home\james\Repos\forked\neth4ck-monorepo\packages\wasm-37\NetHack\src\role.c
  roles: [
    "Archeologist",
    "Barbarian",
    "Caveman",
    "Healer",
    "Knight",
    "Monk",
    "Priest",
    "Rogue",
    "Ranger",
    "Samurai",
    "Tourist",
    "Valkyrie",
    "Wizard",
  ],
  races: ["human", "elf", "dwarf", "gnome", "orc"],
  roleConstraints: {
    Archeologist: {
      races: ["human", "dwarf", "gnome"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    Barbarian: {
      races: ["human", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Caveman: {
      races: ["human", "dwarf", "gnome"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    Healer: {
      races: ["human", "gnome"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    Knight: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Monk: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Priest: {
      races: ["human", "elf"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Rogue: {
      races: ["human", "orc"],
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    Ranger: {
      races: ["human", "elf", "gnome", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Samurai: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Tourist: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    Valkyrie: {
      races: ["human", "dwarf"],
      genders: ["female"],
      aligns: ["lawful", "neutral"],
    },
    Wizard: {
      races: ["human", "elf", "gnome", "orc"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
  },
  raceConstraints: {
    human: {
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    elf: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    dwarf: {
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    gnome: {
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    orc: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
  },
});

const startupSlashEmRuleset = defineStartupCharacterRuleset({
  // Source: \\wsl.localhost\Ubuntu\home\james\Repos\slashem-wasm\slashem-0.0.7E7F3\src\role.c
  roles: [
    "Archeologist",
    "Barbarian",
    "Caveman",
    "Flame Mage",
    "Healer",
    "Ice Mage",
    "Knight",
    "Monk",
    "Necromancer",
    "Priest",
    "Rogue",
    "Ranger",
    "Samurai",
    "Tourist",
    "Undead Slayer",
    "Valkyrie",
    "Wizard",
    "Yeoman",
  ],
  races: [
    "doppelganger",
    "drow",
    "dwarf",
    "elf",
    "gnome",
    "hobbit",
    "human",
    "lycanthrope",
    "orc",
    "vampire",
  ],
  roleConstraints: {
    Archeologist: {
      races: ["human", "elf", "dwarf", "gnome", "hobbit", "vampire"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    Barbarian: {
      races: ["human", "elf", "orc", "lycanthrope", "vampire"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Caveman: {
      races: ["human", "dwarf", "gnome", "vampire"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    "Flame Mage": {
      races: ["human", "elf", "gnome", "orc", "hobbit"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Healer: {
      races: ["human", "elf", "gnome", "hobbit"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    "Ice Mage": {
      races: ["human", "elf", "gnome", "orc", "hobbit", "vampire"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Knight: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Monk: {
      races: ["human", "hobbit"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Necromancer: {
      races: ["human", "elf", "orc", "vampire"],
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    Priest: {
      races: ["human", "elf", "hobbit"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Rogue: {
      races: ["human", "orc", "lycanthrope", "vampire"],
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    Ranger: {
      races: ["human", "elf", "gnome", "orc", "hobbit", "lycanthrope"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Samurai: {
      races: ["human"],
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    Tourist: {
      races: ["human", "hobbit"],
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    "Undead Slayer": {
      races: ["human", "elf", "gnome", "orc", "hobbit", "lycanthrope"],
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    Valkyrie: {
      races: ["human", "dwarf"],
      genders: ["female"],
      aligns: ["lawful", "neutral"],
    },
    Wizard: {
      races: ["human", "elf", "gnome", "orc", "hobbit", "vampire"],
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    Yeoman: {
      races: ["human", "elf", "hobbit"],
      genders: ["male"],
      aligns: ["lawful"],
    },
  },
  raceConstraints: {
    doppelganger: {
      genders: ["male", "female"],
      aligns: ["neutral", "chaotic"],
    },
    drow: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    dwarf: {
      genders: ["male", "female"],
      aligns: ["lawful"],
    },
    elf: {
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    gnome: {
      genders: ["male", "female"],
      aligns: ["neutral"],
    },
    hobbit: {
      genders: ["male", "female"],
      aligns: ["lawful", "neutral"],
    },
    human: {
      genders: ["male", "female"],
      aligns: ["lawful", "neutral", "chaotic"],
    },
    lycanthrope: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    orc: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
    vampire: {
      genders: ["male", "female"],
      aligns: ["chaotic"],
    },
  },
});

export const startupCharacterRulesets: Readonly<
  Record<NethackRuntimeVersion, StartupCharacterRuleset>
> = {
  "3.6.7": startup367Ruleset,
  "3.7": startup37Ruleset,
  slashem: startupSlashEmRuleset,
};

export function getStartupCharacterRuleset(
  runtimeVersion: NethackRuntimeVersion = "3.6.7",
): StartupCharacterRuleset {
  return startupCharacterRulesets[runtimeVersion] ?? startupCharacterRulesets["3.6.7"];
}
