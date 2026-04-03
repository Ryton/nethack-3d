import { mergeTranslations, type LocaleOverrides } from "../locale-helpers";
import { en, type TranslationDictionary } from "./en";

export const fiOverrides: LocaleOverrides<TranslationDictionary> = {
  meta: {
    locale: "fi-FI",
  },
  common: {
    appName: "NetHack 3D -peli",
    confirm: "Vahvista",
    cancel: "Peruuta",
    close: "Sulje",
    back: "Takaisin",
    yes: "KyllÃ¤",
    no: "Ei",
    delete: "Poista",
    edit: "Muokkaa",
    done: "Valmis",
    resetToDefaults: "Palauta oletukset",
    later: "MyÃ¶hemmin",
    checking: "Tarkistetaan...",
    downloading: "Ladataan...",
    canceling: "Peruutetaan...",
    none: "Ei mitÃ¤Ã¤n",
    off: "Pois",
    normal: "Normaali",
    fps: "FPS-tila",
  },
  controller: {
    groups: {
      movement: "Liikkuminen",
      lookAndCamera: "Katse ja kamera",
      actions: "Toiminnot",
      dialogs: "Valintaikkunat",
      system: "JÃ¤rjestelmÃ¤",
    },
    actions: {
      dpad_up: {
        label: "Ohjausristi ylÃ¶s",
        description:
          "Siirry ylÃ¶spÃ¤in valintaikkunoissa ja liikkumisen korostuksessa.",
      },
      dpad_down: {
        label: "Ohjausristi alas",
        description:
          "Siirry alaspÃ¤in valintaikkunoissa ja liikkumisen korostuksessa.",
      },
      dpad_left: {
        label: "Ohjausristi vasemmalle",
        description:
          "Siirry vasemmalle valintaikkunoissa ja liikkumisen korostuksessa.",
      },
      dpad_right: {
        label: "Ohjausristi oikealle",
        description:
          "Siirry oikealle valintaikkunoissa ja liikkumisen korostuksessa.",
      },
      left_stick_up: {
        label: "Vasen sauva ylÃ¶s",
        description: "Liikkumisen korostus ja virtuaalikohdistin ylÃ¶s.",
      },
      left_stick_down: {
        label: "Vasen sauva alas",
        description: "Liikkumisen korostus ja virtuaalikohdistin alas.",
      },
      left_stick_left: {
        label: "Vasen sauva vasemmalle",
        description:
          "Liikkumisen korostus ja virtuaalikohdistin vasemmalle.",
      },
      left_stick_right: {
        label: "Vasen sauva oikealle",
        description: "Liikkumisen korostus ja virtuaalikohdistin oikealle.",
      },
      right_stick_up: {
        label: "Oikea sauva ylÃ¶s",
        description: "Katse, kameran panorointi ja valintaikkunan vieritys ylÃ¶s.",
      },
      right_stick_down: {
        label: "Oikea sauva alas",
        description:
          "Katse, kameran panorointi ja valintaikkunan vieritys alas.",
      },
      right_stick_left: {
        label: "Oikea sauva vasemmalle",
        description: "Katse ja kameran panorointi vasemmalle.",
      },
      right_stick_right: {
        label: "Oikea sauva oikealle",
        description: "Katse ja kameran panorointi oikealle.",
      },
      confirm: {
        label: "Vahvista / Napsauta",
        description: "Vahvista liike ja napsauta valintaikkunoissa.",
      },
      search: {
        label: "Etsi",
        description:
          "Etsi nykyisestÃ¤ ruudusta, kun liikkeen esikatselu ei ole aktiivinen.",
      },
      cancel_or_context: {
        label: "Peruuta / Konteksti",
        description: "Avaa kontekstitoiminnot tai peruuta nykyinen valintaikkuna.",
      },
      action_menu: {
        label: "Toimintovalikko",
        description: "Avaa ohjaimen sÃ¤teittÃ¤inen toimintovalikko.",
      },
      run_modifier: {
        label: "Juoksumuokkain",
        description: "PidÃ¤ painettuna lÃ¤hettÃ¤Ã¤ksesi juoksuetuliitteen ennen liikettÃ¤.",
      },
      zoom_in: {
        label: "Zoomaa (pidÃ¤)",
        description:
          "PidÃ¤ painettuna, ja kÃ¤ytÃ¤ sitten vasenta tai oikeaa sauvaa ylÃ¶s/alas zoomataksesi sisÃ¤Ã¤n tai ulos.",
      },
      recenter_camera: {
        label: "KeskitÃ¤ kamera",
        description: "Palauta kamera pelaajan keskelle.",
      },
      toggle_large_minimap: {
        label: "Vaihda suuri minimikartta",
        description: "Vaihda erittÃ¤in suuren minimikartan koko.",
      },
      pause_menu: {
        label: "Taukovalikko",
        description: "Avaa tai sulje taukovalikko.",
      },
      open_inventory: {
        label: "Tavarat",
        description: "Avaa tavaraikkuna.",
      },
      open_character: {
        label: "Hahmolomake",
        description: "Avaa hahmolomakeikkuna.",
      },
    },
    buttonLabels: {
      0: "A-painike",
      1: "B-painike",
      2: "X-painike",
      3: "Y-painike",
      4: "Vasen olkanappi",
      5: "Oikea olkanappi",
      6: "Vasen liipaisin",
      7: "Oikea liipaisin",
      8: "Takaisin / NÃ¤ytÃ¤",
      9: "Start / Valikko",
      10: "Vasen sauva painallus",
      11: "Oikea sauva painallus",
      12: "Ohjausristi ylÃ¶s",
      13: "Ohjausristi alas",
      14: "Ohjausristi vasemmalle",
      15: "Ohjausristi oikealle",
      16: "Kotipainike",
    },
    axisLabels: {
      0: "Vasen sauva X",
      1: "Vasen sauva Y",
      2: "Oikea sauva X",
      3: "Oikea sauva Y",
    },
    directions: {
      leftStickLeft: "Vasen sauva vasemmalle",
      leftStickRight: "Vasen sauva oikealle",
      leftStickUp: "Vasen sauva ylÃ¶s",
      leftStickDown: "Vasen sauva alas",
      rightStickLeft: "Oikea sauva vasemmalle",
      rightStickRight: "Oikea sauva oikealle",
      rightStickUp: "Oikea sauva ylÃ¶s",
      rightStickDown: "Oikea sauva alas",
    },
    unbound: "Ei sidottu",
    axisFallback: (axisIndex: number) => `Akseli ${axisIndex}`,
    buttonFallback: (buttonIndex: number) => `Painike ${buttonIndex}`,
    slotLabel: (slotIndex: number) => `Paikka ${slotIndex + 1}`,
    listening: "Paina syÃ¶tettÃ¤...",
    clear: "TyhjennÃ¤",
    controllerDetected: (count: number) =>
      `${count} ohjain${count === 1 ? "" : "ta"} havaittu.`,
    noControllerDetected: "Ohjainta ei havaittu.",
  },
  startupInitOptions: {
    accordion: {
      summary: "Alustusasetukset (valinnainen)",
      description:
        "KÃ¤ynnistyksessÃ¤ kÃ¤ytettÃ¤vÃ¤t ylimÃ¤Ã¤rÃ¤iset NetHack `OPTIONS` -mÃ¤Ã¤ritykset. Ikkunaporttiin ja alustaan liittyvÃ¤t asetukset on jÃ¤tetty tarkoituksella pois.",
      resetToDefaults: "Palauta oletukset",
    },
    options: {
      playmode: {
        label: "Pelitila",
        description:
          "Valitse kÃ¤ynnistystila. Wizard-tila on NetHackin debug-tila (`playmode:debug`).",
        options: {
          normal: "Normaali",
          explore: "Tutki",
          debug: "Velho/Debug",
        },
      },
      autopickup: {
        label: "Automaattinen poiminta",
        description:
          "Poimi automaattisesti pickup types -kohdassa valitut esineluokat.",
      },
      pickup_types: {
        label: "Poimintatyypit",
        description:
          'Automaattisesti poimittavien esineluokkien symbolit (esimerkki: $"=/!?+). JÃ¤tÃ¤ tyhjÃ¤ksi kÃ¤yttÃ¤Ã¤ksesi pelin oletusta.',
        placeholder: '$"/=!+?',
      },
      pickup_thrown: {
        label: "Poimi heitetyt esineet",
        description:
          "Poimi heitetyt esineet automaattisesti, kun ne laskeutuvat.",
      },
      pickup_burden: {
        label: "Poiminnan kuormaraja",
        description:
          "Kysy ennen poimintaa, jos tÃ¤mÃ¤ kuormitustaso ylittyisi.",
        options: {
          u: "Kuormittamaton (u)",
          b: "Kuormitettu (b)",
          s: "Rasittunut (s)",
          n: "JÃ¤nnittynyt (n)",
          t: "Ylikuormitettu (t)",
          l: "TÃ¤ysin ylikuormitettu (l)",
        },
      },
      pile_limit: {
        label: "Kasakoko",
        description:
          "EsinemÃ¤Ã¤rÃ¤n raja, joka avaa ponnahdusluettelon lattialla oleville kasoille.",
      },
      autoquiver: {
        label: "Automaattinen viini",
        description:
          "TÃ¤ytÃ¤ viini automaattisesti tai valmistele sopiva ase ammuttaessa.",
      },
      autoopen: {
        label: "Avaa automaattisesti",
        description:
          "YritÃ¤ avata ovet automaattisesti liikkuessa niitÃ¤ kohti.",
      },
      autodig: {
        label: "Kaiva automaattisesti",
        description:
          "Kaiva automaattisesti seiniin, kun se on mahdollista ja liikut niitÃ¤ kohti.",
      },
      cmdassist: {
        label: "Komentojen avustus",
        description:
          "NÃ¤ytÃ¤ ylimÃ¤Ã¤rÃ¤istÃ¤ ohjetekstiÃ¤, kun komennot kirjoitetaan vÃ¤Ã¤rin.",
      },
      confirm: {
        label: "Vahvista hyÃ¶kkÃ¤ykset",
        description: "Kysy ennen rauhanomaisten olentojen hyÃ¶kkÃ¤Ã¤mistÃ¤.",
      },
      safe_pet: {
        label: "Turvallinen lemmikki",
        description: "Kysy ennen kuin osut lemmikkiisi.",
      },
      help: {
        label: "PelinsisÃ¤inen ohje",
        description:
          "Kysy lisÃ¤tietojen nÃ¤yttÃ¤misestÃ¤ look/help-toiminnossa, kun tietoa on enemmÃ¤n saatavilla.",
      },
      legacy: {
        label: "Legacy-intro",
        description: "NÃ¤ytÃ¤ tarinan aloitus, kun uusi peli alkaa.",
      },
      rest_on_space: {
        label: "LepÃ¤Ã¤ vÃ¤lilyÃ¶nnillÃ¤",
        description: "KÃ¤sittele vÃ¤lilyÃ¶ntiÃ¤ odottamisena/lepohetkenÃ¤.",
      },
      pushweapon: {
        label: "SiirrÃ¤ ase",
        description:
          "SiirrÃ¤ tÃ¤llÃ¤ hetkellÃ¤ kÃ¤ytÃ¶ssÃ¤ oleva ase sivukÃ¤teen vaihdettaessa.",
      },
      extmenu: {
        label: "Laajennettu komentovalikko",
        description: "KÃ¤ytÃ¤ ponnahdusvalikkoa laajennetuille komennoille.",
      },
      fixinv: {
        label: "KiinnitÃ¤ tavarapaikat",
        description:
          "YritÃ¤ sÃ¤ilyttÃ¤Ã¤ tavarapaikkojen kirjaimet, kun esineet liikkuvat.",
      },
      implicit_uncursed: {
        label: "NÃ¤ytÃ¤ uncursed",
        description:
          "SisÃ¤llytÃ¤ sana 'uncursed' aina tavarakuvauksiin.",
      },
      mention_walls: {
        label: "Mainitse seinÃ¤t",
        description: "NÃ¤ytÃ¤ viesti liikkuessa seinÃ¤Ã¤ pÃ¤in.",
      },
      sortloot: {
        label: "JÃ¤rjestÃ¤ saalisluettelot",
        description:
          "Lajittelutapa poiminta- ja tavaravalintaluetteloille.",
        options: {
          f: "TÃ¤ysi",
          l: "Vain saalis",
          n: "Ei mitÃ¤Ã¤n",
        },
      },
      sortpack: {
        label: "JÃ¤rjestÃ¤ tavarat",
        description: "JÃ¤rjestÃ¤ repun sisÃ¤ltÃ¶ tyypin mukaan tavaroita nÃ¤ytettÃ¤essÃ¤.",
      },
      msghistory: {
        label: "Viestihistorian koko",
        description:
          "Muistiin sÃ¤ilytettÃ¤vien ylÃ¤rivin viestien lukumÃ¤Ã¤rÃ¤.",
      },
      dogname: {
        label: "Koiran nimi",
        description: "EnsimmÃ¤isen koirasi oletusnimi.",
        placeholder: "Rekku",
      },
      catname: {
        label: "Kissan nimi",
        description: "EnsimmÃ¤isen kissasi oletusnimi.",
        placeholder: "Mirri",
      },
      horsename: {
        label: "Hevosen nimi",
        description: "EnsimmÃ¤isen hevosesi oletusnimi.",
        placeholder: "TÃ¤hti",
      },
      pettype: {
        label: "Suosittu lemmikki",
        description: "Suosittu aloituslemmikin tyyppi rooleille, joilla se voi vaihdella.",
        options: {
          default: "Pelin oletus",
          cat: "Kissa",
          dog: "Koira",
          horse: "Hevonen",
          none: "Ei mitÃ¤Ã¤n",
        },
      },
      fruit: {
        label: "SuosikkihedelmÃ¤",
        description: "HedelmÃ¤tyypin nimi, josta hahmosi pitÃ¤Ã¤.",
        placeholder: "limasieni",
      },
      packorder: {
        label: "Repun jÃ¤rjestys",
        description: "Tavaroissa nÃ¤ytettÃ¤vien esineluokkien jÃ¤rjestys.",
        placeholder: '")[%+/!?=(*0_`',
      },
      paranoid_confirmation: {
        label: "Varmistukset",
        description:
          "VÃ¤lilyÃ¶nneillÃ¤ erotetut lisÃ¤vahvistukset (esim. confirm quit attack pray).",
        placeholder: "attack confirm pray quit",
      },
      sparkle: {
        label: "Taikavastuksen sÃ¤ihke",
        description: "NÃ¤ytÃ¤ erityiset sÃ¤ihketehosteet taikavastukselle.",
      },
      standout: {
        label: "Korostetut hirviÃ¶t/More",
        description: "Lihavoi hirviÃ¶t ja --More-- -kehotteet.",
      },
      tombstone: {
        label: "Hautakivi",
        description: "NÃ¤ytÃ¤ hautakivigrafiikka kuoleman yhteydessÃ¤.",
      },
      verbose: {
        label: "Yksityiskohtaiset viestit",
        description: "KÃ¤ytÃ¤ tÃ¤ydempÃ¤Ã¤ sanamuotoa tila- ja toimintaviesteissÃ¤.",
      },
    },
  },
  soundEffects: {
    byKey: {
      "player-walk": "Pelaajan askel",
      hit: "Osuma",
      "monster-killed": "HirviÃ¶ tapettu (pelaaja)",
      "monster-killed-other": "HirviÃ¶ tapettu (muu)",
      "missed-attack": "Huti",
      "door-opens": "Ovi avautuu",
      "door-closes": "Ovi sulkeutuu",
      "door-kick": "Oven potku",
      "door-smash": "Oven murskaus",
      "door-resists": "Ovi vastustaa",
      "door-distant": "Ovi etÃ¤isyydessÃ¤",
      "walk-down-stairs": "Kulje portaat alas",
      "walk-up-stairs": "Kulje portaat ylÃ¶s",
      eating: "SyÃ¶minen",
      drink: "Juominen",
      "quaff-potion": "Juo juoma",
      "pickup-gold": "Poimi kultaa",
      "pickup-item": "Poimi esine",
      "find-hidden": "LÃ¶ydÃ¤ piilo-ovi/kÃ¤ytÃ¤vÃ¤",
      "level-up": "Tasonnousu",
      unlock: "Avaa lukitus",
      "boulder-push": "Lohkareen tyÃ¶ntÃ¶",
      "boulder-blocked": "Lohkare estetty",
      splash: "Roiske",
      searching: "Etsiminen",
      "magic-cast": "Taian loitsu",
      "magic-heal": "Taikaparannus",
      "magic-buff": "Taikavahvistus",
    },
  },
  characterSheet: {
    titleFallback: "Hahmolomake",
    sectionTitles: {
      overview: "Yleiskuva",
      background: "Tausta",
      basics: "Perusteet",
      characteristics: "Nykyiset ominaisuudet",
      status: "Nykyinen tila",
      attributes: "Nykyiset attribuutit",
    },
    statLabels: {
      strength: "Voima",
      dexterity: "Ketteryys",
      constitution: "KestÃ¤vyys",
      intelligence: "Ã„lykkyys",
      wisdom: "Viisaus",
      charisma: "Karisma",
    },
    commands: {
      enhance: {
        label: "Paranna",
        detail: "Korota taitoja",
      },
      conduct: {
        label: "Haaste",
        detail: "NÃ¤ytÃ¤ haasteen edistyminen",
      },
      overview: {
        label: "Yleiskuva",
        detail: "NÃ¤ytÃ¤ luolaston edistyminen",
      },
      spells: {
        label: "Loitsut",
        detail: "Tarkastele tunnettuja loitsuja",
      },
      seespells: {
        label: "Loitsukirja",
        detail: "Listaa loitsutavarasi",
      },
      technique: {
        label: "Technique",
        detail: "Kayta rooli-/rotukykyja",
      },
      known: {
        label: "LÃ¶ydÃ¶kset",
        detail: "Tunnettujen esineiden luettelo",
      },
      pray: {
        label: "Rukoile",
        detail: "YritÃ¤ rukousta",
      },
    },
  },
  castMenu: {
    schoolLabel: "Koulu:",
    headings: {
      name: "Nimi",
      level: "Taso",
      category: "Luokka",
      fail: "EpÃ¤onn.",
      retention: "SÃ¤ilyvyys",
    },
    summary: {
      known: (count: number) => `${count} tunnettua`,
      castable: (count: number) => `${count} loitsittavaa`,
      bestSuccess: (percent: number) => `Paras onnistuminen ${percent}%`,
      averageFail: (percent: number) => `Keskim. epÃ¤onn. ${percent}%`,
      schoolCount: (count: number) =>
        `${count} koulukunta${count === 1 ? "" : "a"}`,
    },
    retention: {
      unknown: "Tuntematon",
      gone: "Poissa",
      full: "TÃ¤ysi",
    },
  },
  enhanceMenu: {
    defaultGroupTitle: "Taidot",
    availability: {
      available_now: "Saatavilla",
      needs_experience: "Kok./Paikat",
      needs_practice: "Harjoitus",
      maxed_out: "Maksimi",
    },
    summary: {
      available: (count: number) => `${count} saatavilla`,
      gated: (count: number) => `${count} lukittu kokemuksella/paikoilla`,
      practice: (count: number) => `${count} tarvitsee harjoitusta`,
      maxed: (count: number) => `${count} maksimissa`,
    },
    maxLabel: "Maks.",
    slotCount: (count: number) => `${count} paikka${count === 1 ? "" : "a"}`,
  },
  app: {
    unknownTime: "Tuntematon aika",
    debugSession: {
      possibleCrash: "mahdollinen kaatuminen",
      active: "aktiivinen",
    },
    debugLogs: {
      buildLabelAria: (
        buildLabel: string,
        currentCount: number,
        requiredCount: number,
      ) =>
        `Build ${buildLabel}. Hidden debug logging toggle progress ${currentCount} of ${requiredCount}.`,
      enabledToast: "Debug-loki kÃ¤ytÃ¶ssÃ¤",
      enabledLogEntry:
        "Debug-loki otettiin kÃ¤yttÃ¶Ã¶n kÃ¤ynnistyksen build-etiketin easter eggillÃ¤.",
      openLink: "NÃ¤ytÃ¤ debug-lokit",
      clearedLogEntry: "Tallennetut debug-lokit poistettiin kÃ¤yttÃ¤jÃ¤n toimesta.",
    },
    statusEffects: {
      turningToStone: "KivettymÃ¤ssÃ¤",
      slimed: "Limautunut",
      strangled: "Kuristettu",
      foodPoisoning: "Ruokamyrkytys",
      terminallyIll: "Kuolemansairas",
      blind: "Sokea",
      deaf: "Kuuro",
      stunned: "Tainnuksissa",
      confused: "Sekava",
      hallucinating: "Hallusinoi",
      levitating: "Leijuu",
      flying: "LentÃ¤Ã¤",
      riding: "Ratsastaa",
      barehanded: "Paljain kÃ¤sin",
      busy: "Varattu",
      iron: "Rautainen",
      glowingHands: "Hehkuvat kÃ¤det",
      grabbed: "Napattu",
      held: "Pidetty paikallaan",
      icy: "JÃ¤inen",
      inLava: "Laavassa",
      paralyzed: "Halvaantunut",
      sleeping: "Nukkuu",
      slippery: "Liukas",
      submerged: "Upoksissa",
      tethered: "Sidottu",
      trapped: "Loukussa",
      unconscious: "Tajuton",
      woundedLegs: "Haavoittuneet jalat",
      holding: "Pitelee",
    },
    characterStats: {
      descriptions: {
        strength:
          "Vaikuttaa lÃ¤hitaisteluvahinkoon, kantokykyyn ja voimaa vaativiin toimiin.",
        dexterity:
          "Vaikuttaa osumatodennÃ¤kÃ¶isyyteen, ansoihin ja puolustavaan ketteryyteen.",
        constitution:
          "Vaikuttaa HP:n kasvuun sekÃ¤ myrkky- ja imemisvaikutusten kestoon.",
        intelligence:
          "Vaikuttaa lukemiseen ja monien loitsuihin liittyvien toimintojen onnistumiseen.",
        wisdom:
          "Vaikuttaa loitsuenergian kasvuun ja loitsimisen luotettavuuteen.",
        charisma:
          "Vaikuttaa kauppatilanteisiin, lemmikkien kÃ¤sittelyyn ja sosiaalisiin lopputuloksiin.",
      },
      armorClassDescription:
        "Pienempi on parempi. Panssariluokka vÃ¤hentÃ¤Ã¤ vihollisten osumatodennÃ¤kÃ¶isyyttÃ¤ sinuun.",
    },
    directionHelp: {
      controller:
        "Napsauta suuntaa tai kÃ¤ytÃ¤ vasenta sauvaa/ohjausristiÃ¤ esikatseluun ja vapauta vahvistaaksesi. KeskimmÃ¤inen ympyrÃ¤ kohdistaa itseen. KÃ¤ytÃ¤ < tai > portaisiin. Paina ESC peruuttaaksesi.",
      numpad:
        "Napsauta suuntaa. KeskimmÃ¤inen ympyrÃ¤ kohdistaa itseen. Voit myÃ¶s kÃ¤yttÃ¤Ã¤ numeronÃ¤ppÃ¤imistÃ¶Ã¤ (1-4,6-9), nuolinÃ¤ppÃ¤imiÃ¤, <, > tai s. Paina ESC peruuttaaksesi.",
      viKeys:
        "Napsauta suuntaa. KeskimmÃ¤inen ympyrÃ¤ kohdistaa itseen. Voit myÃ¶s kÃ¤yttÃ¤Ã¤ hjkl/yubn-nÃ¤ppÃ¤imiÃ¤, nuolinÃ¤ppÃ¤imiÃ¤, <, > tai s. Paina ESC peruuttaaksesi.",
      fps:
        "Katso tÃ¤hdÃ¤tÃ¤ksesi. Vasen napsautus tai W vahvistaa. S kohdistaa itseen. A/D tai oikea napsautus peruuttaa.",
    },
    inventoryContextActions: {
      apply: "KÃ¤ytÃ¤",
      invoke: "Manaa",
      tip: "Kippaa",
      loot: "RyÃ¶stÃ¤",
      drop: "Pudota",
      eat: "SyÃ¶",
      quaff: "Juo",
      read: "Lue",
      rub: "Hankaa",
      throw: "HeitÃ¤",
      wield: "Kanna kÃ¤dessÃ¤",
      quiver: "Aseta viineen",
      wear: "Pue",
      takeOff: "Riisu",
      putOn: "Laita pÃ¤Ã¤lle",
      remove: "Poista",
      zap: "SÃ¤ihkytÃ¤",
      untrap: "Poista ansa",
      offer: "Uhraa",
      name: "NimeÃ¤",
      call: "Kutsu",
      adjust: "JÃ¤rjestÃ¤",
      engrave: "Kaiverra",
      dip: "Upota",
      info: "Tiedot",
      unwield: "Laske kÃ¤destÃ¤",
    },
    mobileActions: {
      wait: "Odota",
      zap: "SÃ¤ihkytÃ¤",
      cast: "Loitsi",
      kick: "Potkaise",
      read: "Lue",
      quaff: "Juo",
      eat: "SyÃ¶",
      glance: "Vilkaise",
      loot: "RyÃ¶stÃ¤",
      open: "Avaa",
      wield: "Kanna kÃ¤dessÃ¤",
      wear: "Pue",
      putOn: "Laita pÃ¤Ã¤lle",
      takeOff: "Riisu",
      extended: "Laajennetut",
    },
    clientOptions: {
      config: {
        groupControls: "Ohjain ja ensimmÃ¤isen persoonan tila",
        sectionControlsController: "Ohjain",
        controllerEnabled: {
          label: "Ota ohjain kÃ¤yttÃ¶Ã¶n",
          description:
            "Ota peliohjaimen syÃ¶te kÃ¤yttÃ¶Ã¶n pelaamisessa ja kÃ¤yttÃ¶liittymÃ¤n valintaikkunoissa.",
        },
        sectionControlsLook: "Katse ja kamera",
        invertLookYAxis: {
          label: "KÃ¤Ã¤nnÃ¤ Y-akselin katsesuunta",
          description: "KÃ¤Ã¤nnÃ¤ pystysuuntainen hiirikatselu ja kosketuskatselun suunta.",
        },
        fpsLookSensitivityX: {
          label: "FPS-katselun herkkyys X",
          description: "Vaakasuuntainen hiiri-/kosketuskatselun herkkyys.",
        },
        fpsLookSensitivityY: {
          label: "FPS-katselun herkkyys Y",
          description: "Pystysuuntainen hiiri-/kosketuskatselun herkkyys.",
        },
        snapCameraYawToNearest45: {
          label: "Napsauta kameran suunta lÃ¤himpÃ¤Ã¤n 45 asteeseen",
          description:
            "Kun kameran kiertosyÃ¶te vapautetaan, suunta napsahtaa pehmeÃ¤sti lÃ¤himpÃ¤Ã¤n 45 asteen kulmaan.",
        },
        sectionControlsMovement: "Liikkumisen toiminta",
        cameraRelativeMovement: {
          label: "Kameraan suhteutettu liike ja pyyhkÃ¤isyt",
          description:
            "KierrÃ¤ liikenÃ¤ppÃ¤imiÃ¤ ja pyyhkÃ¤isysuuntia kameran Y-akselin kulman perusteella.",
        },
        controllerFpsMoveRepeatMs: {
          label: "FPS-vasemman sauvan liikkeen toisto",
          description:
            "Vasemman sauvan liikkeen toistoviive FPS-tilassa (pienempi on nopeampi).",
        },
        groupInterface: "KÃ¤yttÃ¶liittymÃ¤",
        locale: {
          label: "Kieli",
          description:
            "Valitse kÃ¤yttÃ¶liittymÃ¤n kieli. Oletuksena kÃ¤ytetÃ¤Ã¤n selaimesi aluetta, jos sitÃ¤ tuetaan, ja muuten englantia.",
          options: {
            en: "Englanti",
          },
        },
        sectionDisplayCamera: "Kamera ja nÃ¤kÃ¶kulma",
        fpsMode: {
          label: "EnsimmÃ¤isen persoonan tila",
          description: "KÃ¤ytÃ¤ ensimmÃ¤isen persoonan ohjausta ja hiirikatselua.",
        },
        fpsFlattenEntityBillboards: {
          label: "LitistÃ¤ pÃ¤Ã¤llekkÃ¤iset ruutuspritit",
          description:
            "LitistÃ¤ saaliin tai luolaston kohteiden ruutuspritit, kun niiden pÃ¤Ã¤llÃ¤ seisoo hirviÃ¶, lemmikki tai pelaaja. Poista kÃ¤ytÃ¶stÃ¤ pitÃ¤Ã¤ksesi pÃ¤Ã¤llekkÃ¤iset spritet pystyssÃ¤ olevina billboardeina. Vulture-ruudut pysyvÃ¤t aina pystyssÃ¤.",
        },
        showItemsUnderPlayerInOverheadTilesMode: {
          label: "NÃ¤ytÃ¤ pelaajan alla olevat esineet ylÃ¤kuvaruuduissa",
          description:
            "NÃ¤ytÃ¤ pelaajan alla olevat esineet ja lattiaominaisuudet ylÃ¤kuvaruututilassa ajonaikaisella aluskarttadatalla.",
        },
        fpsFov: {
          label: "FPS-nÃ¤kÃ¶kenttÃ¤",
          description: "SÃ¤Ã¤dÃ¤ ensimmÃ¤isen persoonan kameran nÃ¤kÃ¶kenttÃ¤Ã¤.",
        },
        sectionDisplayGraphics: "Grafiikka ja renderÃ¶inti",
        tilesetMode: {
          label: "NÃ¤yttÃ¶",
          description: "KÃ¤ytÃ¤ graafisia ruutuja ASCII:n sijaan.",
          options: {
            ascii: "ASCII-grafiikka",
            tiles: "Ruudut",
          },
        },
        tilesetPath: {
          label: "Ruutusetti",
          description: "SisÃ¤Ã¤nrakennetut ja ladatut ruutusetit.",
        },
        antialiasing: {
          label: "Reunojen pehmennys",
          description: "3D-renderÃ¶innin reunojen pehmennystila.",
          options: {
            taa: "TAA-pehmennys",
            fxaa: "FXAA-pehmennys",
          },
        },
        lightingEnabled: {
          label: "Valaistus",
          description:
            "Ota kÃ¤yttÃ¶Ã¶n dynaaminen kohtausvalaistus ja luolaston tummennus. Poista kÃ¤ytÃ¶stÃ¤ saadaksesi tasaisemman aina valaistun renderÃ¶innin.",
        },
        blockAmbientOcclusion: {
          label: "YmpÃ¤ristÃ¶n varjostus",
          description:
            "LisÃ¤Ã¤ hienovaraista kontaktivarjostusta lattia- ja seinÃ¤lohkojen vÃ¤liin.",
        },
        brightness: {
          label: "Kirkkaus",
          description: "SÃ¤Ã¤dÃ¤ koko nÃ¤kymÃ¤n kirkkautta.",
        },
        contrast: {
          label: "Kontrasti",
          description: "SÃ¤Ã¤dÃ¤ renderÃ¶idyn nÃ¤kymÃ¤n yleistÃ¤ kontrastia.",
        },
        gamma: {
          label: "GammasÃ¤Ã¤tÃ¶",
          description: "SÃ¤Ã¤dÃ¤ renderÃ¶idyn nÃ¤kymÃ¤n nÃ¤ytÃ¶n gammaa.",
        },
        sectionDisplayInterface: "KÃ¤yttÃ¶liittymÃ¤",
        uiFontScale: {
          label: "KÃ¤yttÃ¶liittymÃ¤n fonttikoko",
          description:
            "Skaalaa kaikkien pelin kÃ¤yttÃ¶liittymÃ¤fonttien kokoa oletusarvoista.",
        },
        disableAnimatedTransitions: {
          label: "Poista animoidut siirtymÃ¤t kÃ¤ytÃ¶stÃ¤",
          description:
            "Poista kÃ¤yttÃ¶liittymÃ¤n hÃ¤ivytys-, liike- ja siirtymÃ¤animaatiot kÃ¤ytÃ¶stÃ¤ nopeampia muutoksia varten.",
        },
        uiTileBackgroundRemoval: {
          label: "Poista ruutujen taustat kÃ¤yttÃ¶liittymÃ¤ssÃ¤",
          description:
            "KÃ¤ytÃ¤ ruutu-/kromaattitaustan poistoa kÃ¤yttÃ¶liittymÃ¤paneeleissa nÃ¤ytettÃ¤viin ruutukuvakkeisiin.",
        },
        desktopTouchInterfaceMode: {
          label: "TyÃ¶pÃ¶ydÃ¤n kosketuskÃ¤yttÃ¶liittymÃ¤",
          description:
            "NÃ¤ytÃ¤ kosketusohjaimet tyÃ¶pÃ¶ydÃ¤llÃ¤ ja valitse pysty- tai vaakasuuntainen asettelu.",
          options: {
            off: "Pois",
            portrait: "KÃ¤ytÃ¤ pystysuuntaista kosketuskÃ¤yttÃ¶liittymÃ¤Ã¤",
            landscape: "KÃ¤ytÃ¤ vaakasuuntaista kosketuskÃ¤yttÃ¶liittymÃ¤Ã¤",
          },
        },
        sectionDisplayMessages: "Viestit ja loki",
        desktopMessageLogWindowScale: {
          label: "TyÃ¶pÃ¶ydÃ¤n viestiloki-ikkunan koko",
          description:
            "Skaalaa kehystetyn tyÃ¶pÃ¶ydÃ¤n viestiloki-ikkunan kokoa muuttamatta fonttikokoa.",
        },
        liveMessageLog: {
          label: "Live-viestiloki",
          description: "NÃ¤ytÃ¤ vierivÃ¤ pelinsisÃ¤inen viestiloki.",
        },
        liveMessageDisplayTimeMs: {
          label: "Live-viestin nÃ¤yttÃ¶aika",
          description:
            "Kuinka kauan kelluva viesti pysyy tÃ¤ysin nÃ¤kyvÃ¤nÃ¤ ennen hÃ¤ivytystÃ¤.",
        },
        liveMessageFadeOutTimeMs: {
          label: "Live-viestin hÃ¤ivytysaika",
          description: "Kelluvan viestin hÃ¤ivytysanimaation kesto.",
        },
        liveMessageLogFontScale: {
          label: "Live-viestien fonttikoko",
          description:
            "Skaalaa ylÃ¶s nousevien kelluvien toimintaviestien kokoa oletusarvosta.",
        },
        sectionDisplayMinimap: "Minikartta",
        minimap: {
          label: "Minikartta",
          description: "NÃ¤ytÃ¤ tai piilota luolaston minikartta.",
        },
        minimapScale: {
          label: "Minikartan koko",
          description: "Skaalaa minikartan kokoa oletusarvosta.",
        },
        sectionDisplayInventory: "Tavaroiden esitystapa",
        reduceInventoryMotion: {
          label: "VÃ¤hennÃ¤ tavaroiden liikettÃ¤",
          description:
            "Poista animoitu tavararivien laajeneminen ja kÃ¤ytÃ¤ yksinkertaisempia vuorovaikutuksia.",
        },
        inventoryTileOnlyMotion: {
          label: "Animoi vain tavararuudut",
          description:
            "Animoi kuvakeruudut pitÃ¤en tavararivien korkeus ja vÃ¤listys kiinteinÃ¤.",
        },
        inventoryFixedTileSize: {
          label: "KiinteÃ¤ tavararuudun koko",
          description:
            "Koskee vain, kun tavaroiden liikkeen vÃ¤hennys on kÃ¤ytÃ¶ssÃ¤. Valitse kiinteÃ¤ kuvakkeen koko.",
          options: {
            none: "Ei mitÃ¤Ã¤n",
            small: "Pieni",
            medium: "Keskikokoinen",
            large: "Suuri",
          },
        },
        groupSound: "Ã„Ã¤ni",
        soundEnabled: {
          label: "Ota Ã¤Ã¤ni kÃ¤yttÃ¶Ã¶n",
          description:
            "Ota FMOD-Ã¤Ã¤ni kÃ¤yttÃ¶Ã¶n tai pois kÃ¤ytÃ¶stÃ¤. Poistaminen vÃ¤hentÃ¤Ã¤ Ã¤Ã¤nenkÃ¤sittelyn kuormaa heikommilla laitteilla.",
        },
        groupMobileControls: "Mobiiliohjaimet",
        invertTouchPanningDirection: {
          label: "Käännä panoroinnin suunta",
          description: "Käännä panoroinnin vetosuunta sen jälkeen, kun pidä ja panoroi alkaa.",
        },
        groupCombat: "Taistelupalaute",
        damageNumbers: {
          label: "Vahinkoluvut",
          description: "NÃ¤ytÃ¤ kelluvat vahinko- ja parannusluvut.",
        },
        displayStatChangesAbovePlayer: {
          label: "NÃ¤ytÃ¤ ominaisuusmuutokset pelaajan ylÃ¤puolella",
          description:
            "NÃ¤ytÃ¤ kelluvat merkinnÃ¤t ominaisuusmuutoksille, kuten Voima ja AC.",
        },
        displayXpGainsAbovePlayer: {
          label: "NÃ¤ytÃ¤ XP-nousut pelaajan ylÃ¤puolella",
          description:
            "NÃ¤ytÃ¤ kelluvat XP-lisÃ¤ysmerkinnÃ¤t kokemuksen kasvaessa.",
        },
        tileShakeOnHit: {
          label: "Ruudun tÃ¤rÃ¤hdys osumasta",
          description: "TÃ¤rÃ¤ytÃ¤ osumaruutuja, kun isku osuu.",
        },
        blood: {
          label: "Veri",
          description: "RenderÃ¶i verisumutyyppiset hiukkastehosteet osumissa.",
        },
        bloodMist: {
          label: "Verisumu",
          description:
            "RenderÃ¶i ilmassa leijuvat verisumuhitukkaset osumissa.",
        },
        bloodGround: {
          label: "Veriroiskeet",
          description:
            "RenderÃ¶i veriroiskeet luolaston lattialle osumien jÃ¤lkeen.",
        },
        bloodDetail: {
          options: {
            veryLow: "ErittÃ¤in matala",
          },
        },
        monsterShatter: {
          label: "HirviÃ¶n pirstoutuminen",
          description:
            "Jaa kukistetut hirviÃ¶billboardit fyysisiksi sirpaleiksi.",
        },
        monsterShatterBloodBorders: {
          label: "Pirstaleiden verireunat",
          description:
            "SÃ¤vytÃ¤ sirpaleiden pikseleitÃ¤ jakoviivojen lÃ¤heltÃ¤ satunnaisilla verenpunaisilla reunoilla.",
        },
        groupCompatibility: "Ajonaikainen yhteensopivuus",
        darkCorridorWalls367: {
          label: "Perinteiset tummat kÃ¤ytÃ¤vÃ¤seinÃ¤t",
          description:
            "PÃ¤Ã¤ttele ja vÃ¤limuistita tummien kÃ¤ytÃ¤vÃ¤seinien ruudut vanhoille NetHack 3.4.3/3.6.x -ajoalustoille, mukaan lukien Slash'EM.",
        },
        overrideNh37DarkCorridorWallTiles: {
          label: "Ohita NetHack 3.7:n tummat seinÃ¤ruudut",
          description:
            "KÃ¤ytÃ¤ tumman seinÃ¤n ohitusasetuksia NetHack 3.7:n tummiin kÃ¤ytÃ¤vÃ¤seinÃ¤n ruutuihin.",
        },
        darkCorridorWallTileOverrideEnabled: {
          label: "Ohita tumma seinÃ¤ruutu",
          description:
            "KÃ¤ytÃ¤ mukautettua atlasruutua tummien seinien ohituksiin, tallennettuna ruutusetin mukaan.",
        },
        darkCorridorWallSolidColorOverrideEnabled: {
          label: "KÃ¤ytÃ¤ tummin seinin yksivÃ¤riÃ¤",
          description: "KÃ¤ytÃ¤ valittua RGB-vÃ¤riÃ¤ ruutusetin ruudun sijaan.",
        },
      },
      tabs: {
        display: {
          label: "NÃ¤yttÃ¶",
          description: "KÃ¤yttÃ¶liittymÃ¤- ja nÃ¤yttÃ¶asetukset.",
        },
        mobile: {
          label: "Mobiili",
          description: "Kosketusohjauksen asetukset mobiilipelaamiseen.",
        },
        controls: {
          label: "Ohjaimet",
          description: "Ohjainsidonnat, FPS-tila ja katselun toiminta.",
        },
        sound: {
          label: "Ã„Ã¤ni",
          description: "Ã„Ã¤nentoisto ja suorituskykyyn liittyvÃ¤t Ã¤Ã¤niasetukset.",
        },
        combat: {
          label: "Taistelu",
          description: "Taistelun osumapalaute ja visuaaliset reaktiot.",
        },
        compatibility: {
          label: "Yhteensopivuus",
          description: "Ajonaikainen yhteensopivuus ja NetHack-kÃ¤ytÃ¶ksen valinnat.",
        },
        updates: {
          label: "PÃ¤ivitykset",
          description:
            "Tarkista pelin verkkopÃ¤ivitykset ja tarkastele odottavia muutoksia.",
        },
      },
    },
    update: {
      loading: {
        startupData: "Ladataan kÃ¤ynnistystietoja...",
        tileset: "Ladataan ruutusettiÃ¤...",
        runtime: "KÃ¤ynnistetÃ¤Ã¤n paikallista runtimea...",
      },
      runtimeStoppedBeforeStartup:
        "Paikallinen NetHack-runtime pysÃ¤htyi ennen kÃ¤ynnistyksen valmistumista.",
      preparingDownload: "Valmistellaan pelipÃ¤ivityksen latausta...",
      idleStatus: "PÃ¤ivityksen tila on joutokÃ¤ynnillÃ¤.",
      fileProgress: (index: number, count: number) =>
        `File ${index} of ${count}`,
      unexpectedCheckFailure: "Odottamaton virhe pÃ¤ivityksen tarkistuksessa.",
      cancelRequested: "Peruutusta pyydetty.",
      stoppingActiveDownloadTask: "PysÃ¤ytetÃ¤Ã¤n aktiivista lataustehtÃ¤vÃ¤Ã¤.",
      unableToCancelDownload: "PÃ¤ivityslatausta ei voitu peruuttaa.",
      noActiveDownloadToCancel: "Ei aktiivista pÃ¤ivityslatausta peruutettavaksi.",
      startingDownload: "Aloitetaan pelipÃ¤ivityksen lataus.",
      canceled: "PÃ¤ivityslataus peruutettiin.",
      unableToDownloadAndApply: "PÃ¤ivityksiÃ¤ ei voitu ladata ja ottaa kÃ¤yttÃ¶Ã¶n.",
      failed: "PÃ¤ivitys epÃ¤onnistui.",
      latestAlreadyInstalled: "Uusin pÃ¤ivitys on jo asennettu.",
      downloadComplete: "PÃ¤ivityslataus valmis.",
      nothingAppliedTryAgain:
        "PÃ¤ivityksiÃ¤ ei otettu kÃ¤yttÃ¶Ã¶n. YritÃ¤ tarkistaa uudelleen.",
      noFilesApplied: "PÃ¤ivitystiedostoja ei otettu kÃ¤yttÃ¶Ã¶n.",
      unexpectedFailure: "Odottamaton pÃ¤ivitysvirhe.",
      checkingForUpdates: "Tarkistetaan GitHub-julkaisuja...",
      unsupportedPlatform:
        "GitHub-julkaisujen tarkistus ei ole saatavilla tÃ¤llÃ¤ alustalla.",
      latestAlreadyInstalledOptions: "Sinulla on jo pelin uusin versio.",
      oneUpdateAvailable:
        "Uudempi peliversio on saatavilla. Haluatko pÃ¤ivittÃ¤Ã¤?",
      manyUpdatesAvailable: (count: number) =>
        `${count} uudempaa peliversiota on saatavilla. Haluatko pÃ¤ivittÃ¤Ã¤?`,
      updateCheckFailed: (message: string) =>
        `GitHub-julkaisujen tarkistus epÃ¤onnistui: ${message}`,
    },
    saves: {
      sections: {
        manual: "Manuaaliset tallennukset",
        autosave: "Automaattitallennukset",
      },
      deleteTitle: "Poistetaanko tallennettu peli?",
      deleteMessage: (name: string) =>
        `Are you sure you want to delete ${name}?`,
      overwriteTitle: "Korvataanko tallennettu peli?",
      overwriteMessage: (name: string) =>
        `A saved game named "${name}" already exists. Do you want to overwrite it with a new character?`,
      errorLoading: "Virhe tallennusten lataamisessa",
      loading: "Ladataan tallennuksia...",
      noneFound: "Tallennettuja pelejÃ¤ ei lÃ¶ytynyt.",
      savedAt: (date: string) => `Saved: ${date}`,
    },
    tilesets: {
      userTileset: "KÃ¤yttÃ¤jÃ¤n ruutusetti",
      currentSelectionFallback: "tÃ¤mÃ¤ ruutusetti",
      deleteUploadedTitle: "Poistetaanko ladattu ruutusetti?",
      deleteUploadedMessage: (label: string) =>
        `Delete '${label}' from uploaded tilesets?`,
      failedToDelete: "Ruutusetin poistaminen epÃ¤onnistui.",
      chooseFile: "Valitse PNG/BMP/GIF/JPEG-ruutusetin tiedosto.",
      provideName: "Anna tÃ¤lle ruutusetille nimi.",
      failedToSave: "Ruutusetin tallentaminen epÃ¤onnistui.",
      failedToLoadUploaded: "Ladattujen ruutusettien lataaminen epÃ¤onnistui:",
      userTilesetSuffix: "KÃ¤yttÃ¤jÃ¤n ruutusetti (kÃ¤yttÃ¤jÃ¤)",
      noTilesetsFound: "RuutusettejÃ¤ ei lÃ¶ytynyt",
      failedToReadImage: "Ruutusetin kuvan lukeminen epÃ¤onnistui.",
    },
    tilePicker: {
      noAtlasAvailable: "Ruutusetin atlasta ei ole saatavilla.",
      unableToLoadAtlas: "Ruutuatlasta ei voitu ladata.",
      atlasLoaded: "Ruutuatlas ladattu.",
      loadingAtlas: "Ladataan ruutuatlasta...",
      selectedTile: (tileId: number) => `Selected: tile #${tileId}`,
      glyph: (label: string) => `Glyph ${label}`,
      tile: (tileId: number) => `Tile ${tileId}`,
      defaultBadge: "Oletus",
      resetToDefault: "Palauta oletus",
      darkWallTitle: "Tumman seinÃ¤ruudun valitsin",
      closeDarkWall: "Sulje tumman seinÃ¤ruudun valitsin",
      closeBackground: "Sulje ruutusetin taustaruudun valitsin",
      backgroundHelper:
        "KÃ¤ytetÃ¤Ã¤n poistamaan jaettu ruutusetin tausta hirviÃ¶-/saalisbillboardeista.",
      backgroundTitle: "Ruutusetin taustaruudun valitsin",
      backgroundTitleWithLabel: (label: string) =>
        `Tileset Background Tile Picker: ${label}`,
      closeSolidColor: "Sulje yksivÃ¤risen kroma-avaimen vÃ¤rivalitsin",
      solidColorTitle: "YksivÃ¤risen kroma-avaimen valitsin",
      solidColorTitleWithLabel: (label: string) =>
        `Solid Color Chroma Key Picker: ${label}`,
    },
    soundPack: {
      discardChangesTitle: "HylÃ¤tÃ¤Ã¤nkÃ¶ Ã¤Ã¤nipaketin muutokset?",
      discardChangesMessage:
        "HylÃ¤tÃ¤Ã¤nkÃ¶ tallentamattomat Ã¤Ã¤nipaketin muutokset ja jatketaan?",
      discard: "HylkÃ¤Ã¤",
      keepEditing: "Jatka muokkausta",
      failedToLoadIndexedDb: "Ã„Ã¤nipakettien lataaminen IndexedDB:stÃ¤ epÃ¤onnistui.",
      failedToSelectRequested: "PyydettyÃ¤ Ã¤Ã¤nipakettia ei voitu valita.",
      provideName: "Anna Ã¤Ã¤nipaketille nimi.",
      created: (name: string) => `Created sound pack '${name}'.`,
      failedToCreate: "Ã„Ã¤nipaketin luonti epÃ¤onnistui.",
      saved: (name: string) => `Saved sound pack '${name}'.`,
      failedToSave: "Ã„Ã¤nipaketin tallennus epÃ¤onnistui.",
      failedToExportZip: "Ã„Ã¤nipaketin ZIP-vienti epÃ¤onnistui.",
      exported: (name: string) => `Exported '${name}'.`,
      failedToImportZip: "Ã„Ã¤nipaketin ZIP-tuonti epÃ¤onnistui.",
      imported: (name: string) => `Imported sound pack '${name}'.`,
      deleteTitle: "Poistetaanko Ã¤Ã¤nipaketti?",
      deleteMessage: (name: string) =>
        `Delete sound pack '${name}'? This cannot be undone.`,
      deleted: (name: string) => `Deleted sound pack '${name}'.`,
      failedToDelete: "Ã„Ã¤nipaketin poistaminen epÃ¤onnistui.",
      noPreviewSource: "TÃ¤lle Ã¤Ã¤nelle ei ole esikatselulÃ¤hdettÃ¤.",
      unableToPreview: "TÃ¤mÃ¤n Ã¤Ã¤nen esikatselu ei onnistu.",
      title: "Ã„Ã¤nipaketit",
      activePack: "Aktiivinen Ã¤Ã¤nipaketti",
      activePackDescription:
        "Valitse aktiivinen Ã¤Ã¤nipaketti, jota kÃ¤ytetÃ¤Ã¤n Ã¤Ã¤nipolkujen ratkaisuun.",
      createNew: "Luo uusi Ã¤Ã¤nipaketti",
      createDescription: "Luo mukautettu Ã¤Ã¤nipaketti, joka ohittaa oletukset.",
      createNameLabel: "Uuden Ã¤Ã¤nipaketin nimi",
      createPlaceholder: "Oma Ã¤Ã¤nipakettini",
      createAndSave: "Luo ja tallenna",
      packName: "Paketin nimi",
      packNameDescription:
        "NimeÃ¤ tÃ¤mÃ¤ paketti uudelleen ja tallenna pÃ¤ivittÃ¤Ã¤ksesi sen Ã¤Ã¤nitiedostojen nimiavaruuden.",
      savePack: "Tallenna Ã¤Ã¤nipaketti",
      export: "Vie Ã¤Ã¤nipaketti",
      import: "Tuo Ã¤Ã¤nipaketti",
      deletePack: "Poista Ã¤Ã¤nipaketti",
      stopPreview: "PysÃ¤ytÃ¤ esikatselu",
      loading: "Ladataan Ã¤Ã¤nipaketteja...",
      pendingSaveSuffix: " (odottaa tallennusta)",
      defaultSuffix: " (oletus)",
      customSuffix: " (mukautettu)",
      noBundledSound: "Ei mukana tulevaa Ã¤Ã¤ntÃ¤",
      enableSoundAria: (label: string) => `Enable ${label}`,
      volumeAria: (label: string) => `Volume for ${label}`,
      play: "Toista",
      playing: "Toistetaan...",
      volume: "Ã„Ã¤nenvoimakkuus",
      remove: "Poista",
      replace: "Korvaa",
      soundFile: "Ã„Ã¤nitiedosto",
      reset: "Palauta",
      attribution: "LÃ¤hdemerkintÃ¤",
      attributionAria: (label: string) => `Attribution for ${label}`,
      attributionPlaceholder: "LÃ¤hde, tekijÃ¤ tai lisenssitiedot",
      addVariation: "+ LisÃ¤Ã¤ variaatio",
    },
    dialogs: {
      pauseMenu: {
        saveBeforeQuit: "Haluatko tallentaa ennen lopettamista?",
        title: "Peli tauolla",
        resume: "Jatka",
        options: "Asetukset",
        saveGame: "Tallenna peli",
        exitToMainMenu: "Palaa pÃ¤Ã¤valikkoon",
        quitGame: "Lopeta peli",
      },
      debugLogs: {
        closeLabel: "Sulje debug-lokit",
        title: "Tallennetut debug-lokit",
        hint: "Lokeja tallennetaan vasta, kun piilotettu debug-lokikytkin on otettu kÃ¤yttÃ¶Ã¶n.",
        showingEntries: (count: number, startedAt: string) =>
          `Showing ${count} entries from ${startedAt}.`,
        noneSaved: "Tallennettuja debug-lokeja ei vielÃ¤ ole.",
        refresh: "PÃ¤ivitÃ¤",
        clearLogs: "TyhjennÃ¤ lokit",
      },
      startupUpdate: {
        maintenanceNotice: "Uudempia GitHub-julkaisuja ei lÃ¶ytynyt.",
        summaryAvailable:
          "Uudempi peliversio on saatavilla. Haluatko pÃ¤ivittÃ¤Ã¤?",
        summaryNone: "Sinulla on jo pelin uusin versio.",
        currentVersion: (version: string) => `Nykyinen versio: ${version}`,
        latestVersion: (version: string) =>
          `Uusin GitHub-julkaisu: ${version}`,
        disableAtStartup:
          "Ã„lÃ¤ nÃ¤ytÃ¤ nÃ¤itÃ¤ ilmoituksia enÃ¤Ã¤ kÃ¤ynnistyksessÃ¤.",
        disabledNotice:
          "KÃ¤ynnistyksen julkaisu-ilmoitukset on nyt poistettu kÃ¤ytÃ¶stÃ¤. Voit ottaa ne uudelleen kÃ¤yttÃ¶Ã¶n asetuksissa.",
        clientUpgradeRequired:
          "Uusimpien alustaparannusten kÃ¤yttÃ¶ vaatii myÃ¶s tÃ¤yden asiakasohjelman pÃ¤ivityksen.",
        progressTitle: "PÃ¤ivityslatauksen tila",
        canceling: "Peruutetaan pÃ¤ivityslatausta...",
        noActiveTransfer: "Ei aktiivista tiedostosiirtoa.",
        waitingForUpdater: "Odotetaan pÃ¤ivittÃ¤jÃ¤n toimintaa.",
        pendingUpdates: "Odottavat pÃ¤ivitykset",
        payloadAvailable: "PÃ¤ivityspaketti on saatavilla.",
        downloadUpdates: "Lataa pÃ¤ivitykset",
        hideDetails: "Piilota tiedot",
        moreDetails: "LisÃ¤Ã¤ tietoja",
        cancelDownload: "Peruuta lataus",
      },
      startup: {
        chooseVariant: "Valitse NetHack-variaatiosi:",
        options: "NetHack 3D -asetukset",
        quitGame: "Lopeta peli",
        chooseSetup: "Valitse hahmosi asetukset:",
        randomCharacter: "Satunnainen hahmo",
        createCharacter: "Luo hahmo",
        loadGame: "Lataa peli",
        selectSavedGame: "Valitse tallennettu peli:",
        enterRandomName: "Anna nimi satunnaiselle hahmollesi:",
        createCharacterPrompt: "Luo hahmosi:",
        name: "Nimi",
        role: "Rooli",
        race: "Rotu",
        gender: "Sukupuoli",
        alignment: "Suuntaus",
        startGame: "Aloita peli",
      },
      clientOptions: {
        closeLabel: "Sulje NetHack 3D -asetukset",
        title: "NetHack 3D:n asiakasasetukset",
        categoriesLabel: "Asetusluokat",
        updates: {
          checkOnLaunchLabel:
            "NÃ¤ytÃ¤ GitHub-julkaisu-ilmoitukset kÃ¤ynnistyksessÃ¤",
          checkOnLaunchDescription:
            "Tarkistaa GitHub-julkaisut kÃ¤ynnistyksessÃ¤ ja ilmoittaa, jos uudempi versio on saatavilla.",
          title: "GitHub-julkaisut",
          description:
            "Vertaa tÃ¤tÃ¤ buildia julkaistuihin GitHub-julkaisuihin.",
          idle:
            "Paina Tarkista pÃ¤ivitykset vertaillaksesi tÃ¤tÃ¤ buildia GitHub-julkaisuihin.",
          button: "Tarkista pÃ¤ivitykset",
          openGitHubReleases: "Avaa GitHub-julkaisut",
        },
        buttons: {
          manageTileSets: "Hallitse ruutusettejÃ¤",
          remapController: "MÃ¤Ã¤ritÃ¤ ohjain uudelleen",
          resetControllerDefaults: "Palauta ohjaimen oletukset",
        },
        hints: {
          darkWallsAlwaysEnabled:
            " Aina kÃ¤ytÃ¶ssÃ¤, kun Vulture-ruudut ovat aktiivisia.",
          darkWallsDisabledByVulture:
            " Pois kÃ¤ytÃ¶stÃ¤, kun Vulture-ruudut ovat aktiivisia.",
          enableDarkWallsFirst:
            " Ota ensin kÃ¤yttÃ¶Ã¶n perinteiset tummat kÃ¤ytÃ¤vÃ¤seinÃ¤t tai NetHack 3.7:n tummien seinien ohitukset.",
          enableFpsFirst: " Ota ensin kÃ¤yttÃ¶Ã¶n ensimmÃ¤isen persoonan tila NÃ¤yttÃ¶-osiossa.",
        },
        darkWallControls: {
          normal: "Normaalitila",
          fps: "FPS-tila",
          normalAria: "Tumman seinÃ¤n yksivÃ¤ri (normaalitila)",
          fpsAria: "Tumman seinÃ¤n yksivÃ¤ri (FPS-tila)",
          gridLines: "Ruudukkoviivat",
          intensity: "Voimakkuus",
        },
        controllerRemap: {
          title: "Ohjaimen uudelleensidonta",
          closeLabel: "Sulje ohjaimen uudelleensidonta",
          hint: "Valitse paikka ja paina sitten nappia tai liikuta sauvaa. Jokaisella toiminnolla on kaksi paikkaa.",
          listeningFor: (label: string, slot: number) =>
            `Listening for ${label} (slot ${slot}). Press ESC to cancel.`,
        },
        resetPrompt:
          "Palautetaanko NetHack 3D:n asetukset oletuksiin? Mukautetut ruutusetit sÃ¤ilyvÃ¤t.",
      },
      tilesetManager: {
        closeLabel: "Sulje ruutusetinhallinta",
        title: "Hallitse ruutusettejÃ¤",
        description:
          "LisÃ¤Ã¤ ruutusettejÃ¤ ja muokkaa ruutusetti-kohtaisia tausta-/kroma-asetuksia.",
        createTitle: "Luo uusi ruutusetti",
        editTitle: "Muokkaa ruutusettiÃ¤",
        editTitleWithName: (label: string) => `Edit Tile Set: ${label}`,
        tileSetName: "Ruutusetin nimi",
        tileSetPlaceholder: "Oma ruutusetti",
        builtInNamesLocked: "SisÃ¤Ã¤nrakennettujen ruutusettien nimiÃ¤ ei voi muuttaa.",
        tileLayoutVersion: "Ruutuasettelun versio",
        layout367: "NetHack 3.6.7 -asettelu",
        layout37: "NetHack 3.7 -asettelu",
        tileLayoutDescription:
          "Valitse tÃ¤mÃ¤n ladatun atlaksen kÃ¤yttÃ¤mÃ¤ ruutuindeksien asettelu.",
        tileImage: "Ruutusetin kuva",
        tileImageOptional: "Ruutusetin kuva (valinnainen korvaus)",
        selectedFile: (fileName: string) => `Selected: ${fileName}`,
        currentFile: (fileName: string) => `Current: ${fileName}`,
        uploadedImage: "ladattu kuva",
        backgroundRemovalDescription:
          "MÃ¤Ã¤ritÃ¤ tÃ¤mÃ¤n ruutusetin billboard-taustan poisto tai jÃ¤tÃ¤ molemmat tilat pois pÃ¤Ã¤ltÃ¤ pitÃ¤Ã¤ksesi atlaksen taustat ennallaan.",
        backgroundTileRemoval: "Taustaruudun poisto",
        backgroundTileRemovalDescription:
          "KÃ¤ytÃ¤ valittua atlasruutua billboard-taustan poistoon.",
        solidChromaKey: "YksivÃ¤rinen kroma-avain",
        solidChromaKeyDescription:
          "KÃ¤ytÃ¤ yhtÃ¤ yhtenÃ¤istÃ¤ RGB-vÃ¤riÃ¤ billboard-taustan poistoon.",
        clickToPickFromAtlas: "napsauta valitaksesi atlaksesta",
        saveFirstThenEdit:
          "Tallenna uusi ruutusetti ensin ja muokkaa sitten tausta-/kroma-asetuksia.",
        createTileSet: "Luo ruutusetti",
        saveTileSet: "Tallenna ruutusetti",
        saveTileSettings: "Tallenna ruutuasetukset",
        importNewTileSet: "+ Tuo uusi ruutusetti",
        noUploadedTilesets: "Ladattuja ruutusettejÃ¤ ei ole saatavilla.",
        selectedSuffix: " (valittu)",
        editingSuffix: " (muokataan)",
        uploadedDetails: (fileName: string, layout: string) =>
          `${fileName} | uploaded | layout ${layout}`,
        builtInDetails: (path: string) => `${path} | built-in`,
      },
      textInput: {
        cancelLabel: "Peruuta tekstinsyÃ¶ttÃ¶",
        placeholder: "SyÃ¶tÃ¤ teksti",
        ok: "HyvÃ¤ksy",
      },
      question: {
        cancelPrompt: "Peruuta kehote",
        selectAll: "Valitse kaikki",
        deselectAll: "Poista kaikkien valinta",
        page: (current: number, total: number) => `Page ${current} / ${total}`,
        pageHintMultiple: "KÃ¤ytÃ¤ < ja > vaihtaaksesi sivua. Paina ESC peruuttaaksesi",
        pageHintSingle: "Paina ESC peruuttaaksesi",
        choices: {
          leftRingFinger: "Vasen nimetÃ¶n",
          rightRingFinger: "Oikea nimetÃ¶n",
          here: "TÃ¤ssÃ¤",
          onGround: "Maassa",
          eligibleItems: "Kelvolliset esineet",
          allInventory: "Koko inventaario",
        },
      },
      runtimeStartError: {
        closeLabel: "Palaa pÃ¤Ã¤valikkoon",
        title: "NetHackin alustaminen epÃ¤onnistui.",
        returnToMainMenu: "Palaa pÃ¤Ã¤valikkoon",
      },
      newGamePrompt: {
        closeLabel: "Sulje uuden pelin kehote",
        title: "Palataanko pÃ¤Ã¤valikkoon?",
        reasonFallback: "Peli ohi",
      },
      direction: {
        cancelLabel: "Peruuta suuntakehote",
      },
      info: {
        closeCharacter: "Sulje hahmoikkuna",
        closeInformation: "Sulje tietoikkuna",
        characterTitle: "Hahmo",
        experienceProgress: "Kokemuksen edistyminen",
        levelLabel: (level: number) => `Level ${level}`,
        xpAtMaxLevel: (xp: string) => `XP ${xp} (max level reached)`,
        xpToNextLevel: (xp: string, next: string, remaining: string) =>
          `XP ${xp} / ${next} â€¢ ${remaining} to next level`,
        vitals: "Perustiedot",
        characteristics: "Ominaisuudet",
        currentLimit: "Nykyinen / Raja",
        armorClass: "Panssariluokka",
        currentStatus: "Nykyinen tila",
        noActiveStatus: "Ei aktiivisia tiloja.",
        currentAttributes: "Nykyiset attribuutit",
        noTemporaryAttributes: "Ei tilapÃ¤isiÃ¤ attribuuttivaikutuksia.",
        characterActions: "Hahmon toiminnot",
        inventory: "Tavarat",
        inventoryDetail: "Avaa kannetut esineet",
        closeHint:
          "Sulje painamalla VÃ„LILYÃ–NTIÃ„, ENTERIÃ„ tai ESCIÃ„. Avaa uudelleen painamalla Ctrl+M.",
        infoTitleFallback: "NetHack-tiedot",
        noDetails: "(Ei tietoja)",
      },
      inventory: {
        closeLabel: "Sulje tavarat",
        title: "TAVARAT",
        empty: "Tavarasi ovat tyhjÃ¤t.",
        unknownItem: "Tuntematon esine",
        closeHint: "Sulje painamalla ENTERIÃ„, ESCIÃ„ tai 'i'.",
        closeHintWithContext:
          "Valitse esine avataksesi kontekstikomennot. Sulje painamalla ENTERIÃ„, ESCIÃ„ tai 'i'",
      },
      inventoryDropMenu: {
        title: "Pudota",
        dropType: "Pudotustapa",
        dropAmount: "PudotusmÃ¤Ã¤rÃ¤",
        dropSpecificAmount: "Pudota tietty mÃ¤Ã¤rÃ¤",
        onlyStackedItems: "Saatavilla vain pinotuille esineille",
      },
      inventoryDropCount: {
        title: "Kuinka monta tÃ¤stÃ¤ pinosta pudotetaan?",
        chooseAmount: (max: number) => `Choose an amount from 1 to ${max}.`,
        ariaLabel: "PudotusmÃ¤Ã¤rÃ¤",
        setMinimum: "Aseta pudotusmÃ¤Ã¤rÃ¤ minimiin",
        decrease: "VÃ¤hennÃ¤ pudotusmÃ¤Ã¤rÃ¤Ã¤ yhdellÃ¤",
        increase: "Kasvata pudotusmÃ¤Ã¤rÃ¤Ã¤ yhdellÃ¤",
        setMaximum: "Aseta pudotusmÃ¤Ã¤rÃ¤ maksimiin",
      },
      mobileActions: {
        extendedCommands: "Laajennetut komennot",
        commonCommands: "Yleiset komennot",
        allCommands: "Kaikki komennot",
        actions: "Toiminnot",
        menu: "Valikko",
        close: "Sulje",
        wizardCommands: "Wizard-komennot",
        wizard: "Wizard-tila",
        repeat: "Toista",
        character: "Hahmo",
        inventory: "Tavarat",
        log: "Loki",
        pickUp: "Poimi",
        search: "Etsi",
        closeMessageLog: "Sulje viestiloki",
      },
      positionPrompt: {
        closeLabel: "Sulje sijaintikehote",
      },
      controllerSupport: {
        prompt: "Ohjain havaittu. Otetaanko ohjaintuki kÃ¤yttÃ¶Ã¶n?",
      },
    },
  },
};

export const fi = mergeTranslations(en, fiOverrides);
