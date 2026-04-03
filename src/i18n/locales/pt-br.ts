import type { LocaleOverrides } from "../locale-helpers";
import type { TranslationDictionary } from "./en";

export const ptBrOverrides = {
  meta: {
    locale: "pt-BR",
  },
  common: {
    appName: "NetHack 3D",
    confirm: "Confirmar",
    cancel: "Cancelar",
    close: "Fechar",
    back: "Voltar",
    yes: "Sim",
    no: "NÃ£o",
    delete: "Excluir",
    edit: "Editar",
    done: "Concluir",
    resetToDefaults: "Restaurar padrÃµes",
    later: "Mais tarde",
    checking: "Verificando...",
    downloading: "Baixando...",
    canceling: "Cancelando...",
    none: "Nenhum",
    off: "Desligado",
    normal: "Normal",
    fps: "FPS",
  },
  controller: {
    groups: {
      movement: "Movimento",
      lookAndCamera: "VisÃ£o e cÃ¢mera",
      actions: "AÃ§Ãµes",
      dialogs: "DiÃ¡logos",
      system: "Sistema",
    },
    actions: {
      dpad_up: {
        label: "Direcional para cima",
        description: "Navega para cima em diÃ¡logos e na prÃ©via de movimento.",
      },
      dpad_down: {
        label: "Direcional para baixo",
        description: "Navega para baixo em diÃ¡logos e na prÃ©via de movimento.",
      },
      dpad_left: {
        label: "Direcional para a esquerda",
        description:
          "Navega para a esquerda em diÃ¡logos e na prÃ©via de movimento.",
      },
      dpad_right: {
        label: "Direcional para a direita",
        description:
          "Navega para a direita em diÃ¡logos e na prÃ©via de movimento.",
      },
      left_stick_up: {
        label: "AnalÃ³gico esquerdo para cima",
        description: "PrÃ©via de movimento e cursor virtual para cima.",
      },
      left_stick_down: {
        label: "AnalÃ³gico esquerdo para baixo",
        description: "PrÃ©via de movimento e cursor virtual para baixo.",
      },
      left_stick_left: {
        label: "AnalÃ³gico esquerdo para a esquerda",
        description: "PrÃ©via de movimento e cursor virtual para a esquerda.",
      },
      left_stick_right: {
        label: "AnalÃ³gico esquerdo para a direita",
        description: "PrÃ©via de movimento e cursor virtual para a direita.",
      },
      right_stick_up: {
        label: "AnalÃ³gico direito para cima",
        description: "Olhar, mover a cÃ¢mera e rolar diÃ¡logos para cima.",
      },
      right_stick_down: {
        label: "AnalÃ³gico direito para baixo",
        description: "Olhar, mover a cÃ¢mera e rolar diÃ¡logos para baixo.",
      },
      right_stick_left: {
        label: "AnalÃ³gico direito para a esquerda",
        description: "Olhar e mover a cÃ¢mera para a esquerda.",
      },
      right_stick_right: {
        label: "AnalÃ³gico direito para a direita",
        description: "Olhar e mover a cÃ¢mera para a direita.",
      },
      confirm: {
        label: "Confirmar / Clique",
        description: "Confirma movimentos e clica em diÃ¡logos.",
      },
      search: {
        label: "Procurar",
        description:
          "Procura no quadrado atual quando nÃ£o houver prÃ©via de movimento ativa.",
      },
      cancel_or_context: {
        label: "Cancelar / Contexto",
        description: "Abre aÃ§Ãµes de contexto ou cancela o diÃ¡logo atual.",
      },
      action_menu: {
        label: "Menu de aÃ§Ãµes",
        description: "Abre o menu radial de aÃ§Ãµes do controle.",
      },
      run_modifier: {
        label: "Modificador de corrida",
        description:
          "Segure para enviar o prefixo de corrida antes do movimento.",
      },
      zoom_in: {
        label: "Zoom (segurar)",
        description:
          "Segure e use o analÃ³gico esquerdo ou direito para cima/baixo para aproximar ou afastar.",
      },
      recenter_camera: {
        label: "Recentralizar cÃ¢mera",
        description: "Retorna a cÃ¢mera ao centro do jogador.",
      },
      toggle_large_minimap: {
        label: "Alternar minimapa grande",
        description: "Alterna o tamanho do minimapa muito grande.",
      },
      pause_menu: {
        label: "Menu de pausa",
        description: "Abre ou fecha o menu de pausa.",
      },
      open_inventory: {
        label: "InventÃ¡rio",
        description: "Abre a janela de inventÃ¡rio.",
      },
      open_character: {
        label: "Ficha do personagem",
        description: "Abre a janela da ficha do personagem.",
      },
    },
    buttonLabels: {
      0: "A",
      1: "B",
      2: "X",
      3: "Y",
      4: "BotÃ£o superior esquerdo",
      5: "BotÃ£o superior direito",
      6: "Gatilho esquerdo",
      7: "Gatilho direito",
      8: "Voltar / Exibir",
      9: "Iniciar / Menu",
      10: "Clique no analÃ³gico esquerdo",
      11: "Clique no analÃ³gico direito",
      12: "Direcional para cima",
      13: "Direcional para baixo",
      14: "Direcional para a esquerda",
      15: "Direcional para a direita",
      16: "InÃ­cio",
    },
    axisLabels: {
      0: "AnalÃ³gico esquerdo X",
      1: "AnalÃ³gico esquerdo Y",
      2: "AnalÃ³gico direito X",
      3: "AnalÃ³gico direito Y",
    },
    directions: {
      leftStickLeft: "AnalÃ³gico esquerdo para a esquerda",
      leftStickRight: "AnalÃ³gico esquerdo para a direita",
      leftStickUp: "AnalÃ³gico esquerdo para cima",
      leftStickDown: "AnalÃ³gico esquerdo para baixo",
      rightStickLeft: "AnalÃ³gico direito para a esquerda",
      rightStickRight: "AnalÃ³gico direito para a direita",
      rightStickUp: "AnalÃ³gico direito para cima",
      rightStickDown: "AnalÃ³gico direito para baixo",
    },
    unbound: "Sem atribuiÃ§Ã£o",
    axisFallback: (axisIndex: number) => `Eixo ${axisIndex}`,
    buttonFallback: (buttonIndex: number) => `BotÃ£o ${buttonIndex}`,
    slotLabel: (slotIndex: number) => `Slot ${slotIndex + 1}`,
    listening: "Aguardando entrada...",
    clear: "Limpar",
    controllerDetected: (count: number) =>
      `${count} controle${count === 1 ? "" : "s"} detectado${count === 1 ? "" : "s"}.`,
    noControllerDetected: "Nenhum controle detectado.",
  },
  startupInitOptions: {
    accordion: {
      summary: "OpÃ§Ãµes de inicializaÃ§Ã£o (opcional)",
      description:
        "Entradas extras de `OPTIONS` do NetHack aplicadas na inicializaÃ§Ã£o. OpÃ§Ãµes especÃ­ficas de plataforma e de window-port foram omitidas de propÃ³sito.",
      resetToDefaults: "Restaurar padrÃµes",
    },
    options: {
      playmode: {
        label: "Modo de jogo",
        description:
          "Escolha o modo inicial. O modo assistente Ã© o modo de depuraÃ§Ã£o do NetHack (`playmode:debug`).",
        options: {
          normal: "Normal",
          explore: "ExploraÃ§Ã£o",
          debug: "Assistente/DepuraÃ§Ã£o",
        },
      },
      autopickup: {
        label: "Coleta automÃ¡tica",
        description:
          "Coleta automaticamente as classes de itens selecionadas em tipos de coleta.",
      },
      pickup_types: {
        label: "Tipos de coleta",
        description:
          'SÃ­mbolos de classes de objeto para coleta automÃ¡tica (exemplo: $"=/!?+). Deixe em branco para usar o padrÃ£o do jogo.',
        placeholder: '$"=/!?+',
      },
      pickup_thrown: {
        label: "Coletar itens arremessados",
        description:
          "Coleta automaticamente itens arremessados quando eles caem no chÃ£o.",
      },
      pickup_burden: {
        label: "Limite de carga para coleta",
        description:
          "Pergunta antes de coletar quando esse nÃ­vel de carga seria ultrapassado.",
        options: {
          u: "Sem carga (u)",
          b: "Carregado (b)",
          s: "Sobrecarregado (s)",
          n: "Tenso (n)",
          t: "Muito sobrecarregado (t)",
          l: "Excesso de carga (l)",
        },
      },
      pile_limit: {
        label: "Limite de pilha",
        description:
          "Quantidade de itens que aciona uma lista em popup para pilhas no chÃ£o.",
      },
      autoquiver: {
        label: "Aljava automÃ¡tica",
        description:
          "Preenche a aljava automaticamente ou prepara uma arma adequada ao atirar.",
      },
      autoopen: {
        label: "Abrir automaticamente",
        description:
          "Tenta abrir portas automaticamente ao se mover em direÃ§Ã£o a elas.",
      },
      autodig: {
        label: "Escavar automaticamente",
        description:
          "Escava automaticamente paredes quando possÃ­vel ao se mover contra elas.",
      },
      cmdassist: {
        label: "AssistÃªncia de comandos",
        description:
          "Mostra texto de ajuda extra quando comandos sÃ£o digitados incorretamente.",
      },
      confirm: {
        label: "Confirmar ataques",
        description: "Pergunta antes de atacar criaturas pacÃ­ficas.",
      },
      safe_pet: {
        label: "Proteger mascote",
        description: "Pergunta antes de atingir seu mascote.",
      },
      help: {
        label: "Ajuda no jogo",
        description:
          "Pergunta se deve mostrar detalhes extras de observaÃ§Ã£o/ajuda quando houver mais informaÃ§Ãµes.",
      },
      legacy: {
        label: "IntroduÃ§Ã£o clÃ¡ssica",
        description: "Mostra a introduÃ§Ã£o da histÃ³ria ao iniciar um novo jogo.",
      },
      rest_on_space: {
        label: "Descansar com espaÃ§o",
        description: "Trata a tecla de espaÃ§o como esperar/descansar.",
      },
      pushweapon: {
        label: "Empurrar arma",
        description: "Move a arma empunhada para a mÃ£o secundÃ¡ria ao trocar.",
      },
      extmenu: {
        label: "Menu de comandos estendidos",
        description: "Usa um menu popup para comandos estendidos.",
      },
      fixinv: {
        label: "Fixar letras do inventÃ¡rio",
        description:
          "Tenta preservar as letras do inventÃ¡rio conforme os itens mudam.",
      },
      implicit_uncursed: {
        label: "Mostrar 'nÃ£o amaldiÃ§oado'",
        description:
          "Sempre inclui a expressÃ£o 'nÃ£o amaldiÃ§oado' nas descriÃ§Ãµes do inventÃ¡rio.",
      },
      mention_walls: {
        label: "Mencionar paredes",
        description: "Mostra uma mensagem ao se mover contra uma parede.",
      },
      sortloot: {
        label: "Ordenar listas de saque",
        description:
          "Comportamento de ordenaÃ§Ã£o para listas de coleta e seleÃ§Ã£o do inventÃ¡rio.",
        options: {
          f: "Completo",
          l: "Apenas saque",
          n: "Nenhum",
        },
      },
      sortpack: {
        label: "Ordenar inventÃ¡rio",
        description:
          "Ordena o conteÃºdo da mochila por tipo ao exibir o inventÃ¡rio.",
      },
      msghistory: {
        label: "Tamanho do histÃ³rico de mensagens",
        description:
          "NÃºmero de mensagens da linha superior mantidas para consulta.",
      },
      dogname: {
        label: "Nome do cachorro",
        description: "Nome padrÃ£o para seu primeiro cachorro.",
        placeholder: "Fido",
      },
      catname: {
        label: "Nome do gato",
        description: "Nome padrÃ£o para seu primeiro gato.",
        placeholder: "Morris",
      },
      horsename: {
        label: "Nome do cavalo",
        description: "Nome padrÃ£o para seu primeiro cavalo.",
        placeholder: "Silver",
      },
      pettype: {
        label: "Mascote preferido",
        description:
          "Tipo de mascote inicial preferido para papÃ©is que podem variar.",
        options: {
          default: "PadrÃ£o do jogo",
          cat: "Gato",
          dog: "Cachorro",
          horse: "Cavalo",
          none: "Nenhum",
        },
      },
      fruit: {
        label: "Fruta preferida",
        description: "Nome do tipo de fruta preferido do seu personagem.",
        placeholder: "bolor gosmento",
      },
      packorder: {
        label: "Ordem da mochila",
        description: "Ordem das classes de itens exibidas no inventÃ¡rio.",
        placeholder: '")[%?+/=!(*0_`',
      },
      paranoid_confirmation: {
        label: "ConfirmaÃ§Ã£o paranoica",
        description:
          "ConfirmaÃ§Ãµes extras separadas por espaÃ§o (exemplo: confirm quit attack pray).",
        placeholder: "confirm quit attack pray",
      },
      sparkle: {
        label: "Brilho da resistÃªncia mÃ¡gica",
        description:
          "Mostra efeitos especiais de brilho para resistÃªncia mÃ¡gica.",
      },
      standout: {
        label: "Monstros/--More-- destacados",
        description: "Destaca monstros e prompts de --More-- em negrito.",
      },
      tombstone: {
        label: "LÃ¡pide",
        description: "Mostra a lÃ¡pide ao morrer.",
      },
      verbose: {
        label: "Mensagens detalhadas",
        description:
          "Usa textos mais completos para mensagens de status e aÃ§Ãµes.",
      },
    },
  },
  soundEffects: {
    byKey: {
      "player-walk": "Passos do jogador",
      hit: "Golpe",
      "thrown-weapon": "Arma arremessada",
      "monster-killed": "Monstro morto (jogador)",
      "monster-killed-other": "Monstro morto (outro)",
      "missed-attack": "Ataque errou",
      "door-opens": "Porta abre",
      "door-closes": "Porta fecha",
      "door-kick": "Chute na porta",
      "door-smash": "Arrebentar porta",
      "door-resists": "A porta resiste",
      "door-distant": "Porta ao longe",
      "walk-down-stairs": "Descer escadas",
      "walk-up-stairs": "Subir escadas",
      eating: "Comendo",
      drink: "Beber",
      "quaff-potion": "Beber uma poÃ§Ã£o",
      "pickup-gold": "Pegar ouro",
      "pickup-item": "Pegar item",
      "find-hidden": "Encontrar porta/passagem secreta",
      "level-up": "Subir de nÃ­vel",
      unlock: "Destrancar",
      "boulder-push": "Empurrar pedra",
      "boulder-blocked": "Pedra bloqueada",
      splash: "Respingo",
      searching: "Procurando",
      "magic-cast": "LanÃ§ar magia",
      "magic-heal": "Cura mÃ¡gica",
      "magic-buff": "BÃ´nus mÃ¡gico",
    },
  },
  characterSheet: {
    titleFallback: "Ficha do personagem",
    sectionTitles: {
      overview: "VisÃ£o geral",
      background: "HistÃ³rico",
      basics: "BÃ¡sico",
      characteristics: "CaracterÃ­sticas atuais",
      status: "Estado atual",
      attributes: "Atributos atuais",
    },
    statLabels: {
      strength: "ForÃ§a",
      dexterity: "Destreza",
      constitution: "ConstituiÃ§Ã£o",
      intelligence: "InteligÃªncia",
      wisdom: "Sabedoria",
      charisma: "Carisma",
    },
    commands: {
      enhance: {
        label: "Aprimorar",
        detail: "Evoluir perÃ­cias",
      },
      conduct: {
        label: "Conduta",
        detail: "Mostrar progresso do desafio",
      },
      overview: {
        label: "VisÃ£o geral",
        detail: "Mostrar progresso na masmorra",
      },
      spells: {
        label: "Magias",
        detail: "Revisar magias conhecidas",
      },
      seespells: {
        label: "Livro de magias",
        detail: "Listar inventÃ¡rio de magias",
      },
      technique: {
        label: "Tecnica",
        detail: "Usar habilidades de funcao/raca",
      },
      known: {
        label: "Descobertas",
        detail: "Lista de objetos conhecidos",
      },
      pray: {
        label: "Rezar",
        detail: "Tentar rezar",
      },
    },
  },
  castMenu: {
    schoolLabel: "Escola:",
    headings: {
      name: "Nome",
      level: "NÃ­vel",
      category: "Categoria",
      fail: "Falha",
      retention: "RetenÃ§Ã£o",
    },
    summary: {
      known: (count: number) => `${count} conhecidas`,
      castable: (count: number) => `${count} lanÃ§Ã¡veis`,
      bestSuccess: (percent: number) => `Melhor sucesso ${percent}%`,
      averageFail: (percent: number) => `Falha mÃ©dia ${percent}%`,
      schoolCount: (count: number) =>
        `${count} escola${count === 1 ? "" : "s"}`,
    },
    retention: {
      unknown: "Desconhecida",
      gone: "Perdida",
      full: "100%",
    },
  },
  enhanceMenu: {
    defaultGroupTitle: "PerÃ­cias",
    availability: {
      available_now: "DisponÃ­vel",
      needs_experience: "Exp./Slots",
      needs_practice: "PrÃ¡tica",
      maxed_out: "No mÃ¡ximo",
    },
    summary: {
      available: (count: number) => `${count} disponÃ­veis`,
      gated: (count: number) => `${count} bloqueadas por experiÃªncia/slots`,
      practice: (count: number) => `${count} precisam de prÃ¡tica`,
      maxed: (count: number) => `${count} no mÃ¡ximo`,
    },
    maxLabel: "MÃ¡x",
    slotCount: (count: number) => `${count} slot${count === 1 ? "" : "s"}`,
  },
  app: {
    unknownTime: "HorÃ¡rio desconhecido",
    debugSession: {
      possibleCrash: "possÃ­vel falha",
      active: "ativa",
    },
    debugLogs: {
      buildLabelAria: (
        buildLabel: string,
        currentCount: number,
        requiredCount: number,
      ) =>
        `Build ${buildLabel}. Progresso do alternador oculto de logs de depuraÃ§Ã£o: ${currentCount} de ${requiredCount}.`,
      enabledToast: "Log de depuraÃ§Ã£o ativado",
      enabledLogEntry:
        "Log de depuraÃ§Ã£o ativado pelo easter egg do rÃ³tulo da build inicial.",
      openLink: "Ver logs de depuraÃ§Ã£o",
      clearedLogEntry: "Logs de depuraÃ§Ã£o salvos foram limpos pelo usuÃ¡rio.",
    },
    statusEffects: {
      turningToStone: "Virando pedra",
      slimed: "Coberto de limo",
      strangled: "Estrangulado",
      foodPoisoning: "Envenenamento alimentar",
      terminallyIll: "Gravemente doente",
      blind: "Cego",
      deaf: "Surdo",
      stunned: "Atordoado",
      confused: "Confuso",
      hallucinating: "Alucinando",
      levitating: "Levitando",
      flying: "Voando",
      riding: "Montado",
      barehanded: "Desarmado",
      busy: "Ocupado",
      iron: "Ferro",
      glowingHands: "MÃ£os brilhantes",
      grabbed: "Agarrado",
      held: "Preso",
      icy: "Congelado",
      inLava: "Na lava",
      paralyzed: "Paralisado",
      sleeping: "Dormindo",
      slippery: "Escorregadio",
      submerged: "Submerso",
      tethered: "Amarrado",
      trapped: "Preso em armadilha",
      unconscious: "Inconsciente",
      woundedLegs: "Pernas feridas",
      holding: "Segurando",
    },
    characterStats: {
      descriptions: {
        strength:
          "Afeta dano corpo a corpo, capacidade de carga e aÃ§Ãµes de forÃ§a.",
        dexterity:
          "Afeta chance de acerto, interaÃ§Ã£o com armadilhas e agilidade defensiva.",
        constitution:
          "Afeta crescimento de PV e resistÃªncia a veneno e drenagem.",
        intelligence:
          "Afeta leitura e sucesso em muitas aÃ§Ãµes relacionadas a magia.",
        wisdom:
          "Afeta crescimento de energia mÃ¡gica e confiabilidade ao lanÃ§ar magias.",
        charisma:
          "Afeta interaÃ§Ãµes em lojas, manejo de mascotes e resultados sociais.",
      },
      armorClassDescription:
        "Quanto menor, melhor. A classe de armadura reduz a chance de o inimigo acertar vocÃª.",
    },
    directionHelp: {
      controller:
        "Clique em uma direÃ§Ã£o ou use o analÃ³gico esquerdo/DPAD para prÃ©-visualizar e solte para confirmar. O cÃ­rculo central mira em vocÃª. Use < ou > para escadas. Pressione ESC para cancelar.",
      numpad:
        "Clique em uma direÃ§Ã£o. O cÃ­rculo central mira em vocÃª. VocÃª tambÃ©m pode usar o teclado numÃ©rico (1-4,6-9), setas, <, > ou s. Pressione ESC para cancelar.",
      viKeys:
        "Clique em uma direÃ§Ã£o. O cÃ­rculo central mira em vocÃª. VocÃª tambÃ©m pode usar hjkl/yubn, setas, <, > ou s. Pressione ESC para cancelar.",
      fps: "Olhe para mirar. Clique esquerdo ou W confirma. S mira em vocÃª. A/D ou clique direito cancela.",
    },
    inventoryContextActions: {
      apply: "Aplicar",
      invoke: "Invocar",
      tip: "Dica",
      loot: "Saquear",
      drop: "Largar",
      eat: "Comer",
      quaff: "Beber",
      read: "Ler",
      rub: "Esfregar",
      throw: "Arremessar",
      wield: "Empunhar",
      quiver: "Colocar na aljava",
      wear: "Vestir",
      takeOff: "Tirar",
      putOn: "Colocar",
      remove: "Remover",
      zap: "Disparar",
      untrap: "Desarmar",
      offer: "Oferecer",
      name: "Nomear",
      call: "Chamar",
      adjust: "Ajustar",
      engrave: "Gravar",
      dip: "Mergulhar",
      info: "InformaÃ§Ãµes",
      unwield: "Desequipar",
    },
    mobileActions: {
      wait: "Esperar",
      zap: "Disparar",
      cast: "LanÃ§ar",
      kick: "Chutar",
      read: "Ler",
      quaff: "Beber",
      eat: "Comer",
      glance: "Olhar",
      loot: "Saquear",
      open: "Abrir",
      wield: "Empunhar",
      wear: "Vestir",
      putOn: "Colocar",
      takeOff: "Tirar",
      extended: "Expandido",
    },
    clientOptions: {
      config: {
        groupControls: "Controle e modo em primeira pessoa",
        sectionControlsController: "Controle",
        controllerEnabled: {
          label: "Ativar suporte a controle",
          description:
            "Ativa entrada de gamepad para a jogabilidade e diÃ¡logos da interface.",
        },
        sectionControlsLook: "VisÃ£o e cÃ¢mera",
        invertLookYAxis: {
          label: "Inverter visÃ£o no eixo Y",
          description:
            "Inverte a direÃ§Ã£o vertical do mouselook e do olhar por toque.",
        },
        fpsLookSensitivityX: {
          label: "Sensibilidade de visÃ£o FPS X",
          description: "Sensibilidade horizontal do mouselook/olhar por toque.",
        },
        fpsLookSensitivityY: {
          label: "Sensibilidade de visÃ£o FPS Y",
          description: "Sensibilidade vertical do mouselook/olhar por toque.",
        },
        snapCameraYawToNearest45: {
          label: "Ajustar rotaÃ§Ã£o da cÃ¢mera para 45 graus",
          description:
            "Quando a entrada de rotaÃ§Ã£o da cÃ¢mera Ã© solta, ajusta suavemente o Ã¢ngulo para o mÃºltiplo de 45 graus mais prÃ³ximo.",
        },
        sectionControlsMovement: "Comportamento de movimento",
        cameraRelativeMovement: {
          label: "Movimento e gestos relativos Ã  cÃ¢mera",
          description:
            "Gira teclas de movimento e direÃ§Ãµes de gesto com base no Ã¢ngulo do eixo Y da cÃ¢mera.",
        },
        controllerFpsMoveRepeatMs: {
          label: "RepetiÃ§Ã£o de movimento FPS no analÃ³gico esquerdo",
          description:
            "Atraso de repetiÃ§Ã£o de movimento do analÃ³gico esquerdo no modo FPS (menor Ã© mais rÃ¡pido).",
        },
        groupInterface: "Interface do jogo",
        locale: {
          label: "Idioma",
          description:
            "Escolha o idioma da interface. O padrÃ£o usa a regiÃ£o do navegador quando houver suporte, com inglÃªs como fallback.",
          options: {
            en: "InglÃªs",
          },
        },
        sectionDisplayCamera: "CÃ¢mera e perspectiva",
        fpsMode: {
          label: "Modo em primeira pessoa",
          description: "Usa controles em primeira pessoa e mouselook.",
        },
        fpsFlattenEntityBillboards: {
          label: "Achatar sprites de tiles sobrepostos",
          description:
            "Achata sprites de tiles de saque ou elementos da masmorra quando monstros, mascotes ou o jogador ficam sobre eles. Desative para manter sprites sobrepostos como billboards em pÃ©. Tiles de Vulture sempre permanecem em pÃ©.",
        },
        showItemsUnderPlayerInOverheadTilesMode: {
          label: "Mostrar itens sob o jogador em tiles superiores",
          description:
            "Mostra itens e elementos do chÃ£o sob o jogador no modo de tiles superiores usando dados de glifos de camada inferior em tempo de execuÃ§Ã£o.",
        },
        fpsFov: {
          label: "Campo de visÃ£o do FPS",
          description: "Ajusta o campo de visÃ£o da cÃ¢mera em primeira pessoa.",
        },
        sectionDisplayGraphics: "GrÃ¡ficos e renderizaÃ§Ã£o",
        tilesetMode: {
          label: "ExibiÃ§Ã£o",
          description: "Usa tiles grÃ¡ficos em vez de ASCII.",
          options: {
            ascii: "ASCII",
            tiles: "Tiles",
          },
        },
        tilesetPath: {
          label: "Conjunto de tiles",
          description: "Tilesets internos e enviados.",
        },
        antialiasing: {
          label: "SuavizaÃ§Ã£o de bordas",
          description: "Modo de suavizaÃ§Ã£o de bordas para renderizaÃ§Ã£o 3D.",
          options: {
            taa: "TAA",
            fxaa: "FXAA",
          },
        },
        lightingEnabled: {
          label: "IluminaÃ§Ã£o",
          description:
            "Ativa iluminaÃ§Ã£o dinÃ¢mica da cena e escurecimento da masmorra. Desative para uma renderizaÃ§Ã£o plana e sempre iluminada.",
        },
        blockAmbientOcclusion: {
          label: "OclusÃ£o de ambiente",
          description:
            "Adiciona um sombreado sutil de contato entre blocos de piso e parede.",
        },
        brightness: {
          label: "Brilho",
          description: "Ajusta o brilho geral da cena.",
        },
        contrast: {
          label: "Contraste",
          description: "Ajusta o contraste global do conteÃºdo renderizado.",
        },
        gamma: {
          label: "Gama",
          description: "Ajusta a gama de exibiÃ§Ã£o do conteÃºdo renderizado.",
        },
        sectionDisplayInterface: "Interface do jogo",
        uiFontScale: {
          label: "Escala da fonte da interface",
          description:
            "Escala todos os tamanhos de fonte da interface do jogo a partir dos valores padrÃ£o.",
        },
        disableAnimatedTransitions: {
          label: "Desativar transiÃ§Ãµes animadas",
          description:
            "Desativa animaÃ§Ãµes de fade, movimento e transiÃ§Ã£o da interface para mudanÃ§as mais rÃ¡pidas.",
        },
        uiTileBackgroundRemoval: {
          label: "Remover fundos de tiles na interface",
          description:
            "Aplica remoÃ§Ã£o de fundo por tile/chroma aos Ã­cones exibidos nos painÃ©is da interface.",
        },
        desktopTouchInterfaceMode: {
          label: "Interface de toque no desktop",
          description:
            "Mostra controles de toque no desktop e permite escolher layout retrato ou paisagem.",
          options: {
            off: "Desligado",
            portrait: "Usar interface de toque em retrato",
            landscape: "Usar interface de toque em paisagem",
          },
        },
        sectionDisplayMessages: "Mensagens e registro",
        desktopMessageLogWindowScale: {
          label: "Escala da janela de registro de mensagens no desktop",
          description:
            "Escala o tamanho da janela emoldurada do registro de mensagens sem alterar o tamanho da fonte.",
        },
        liveMessageLog: {
          label: "Registro de mensagens ao vivo",
          description: "Exibe o registro de mensagens rolÃ¡vel dentro do jogo.",
        },
        liveMessageDisplayTimeMs: {
          label: "Tempo de exibiÃ§Ã£o das mensagens ao vivo",
          description:
            "Tempo em que uma mensagem flutuante permanece totalmente visÃ­vel antes de desaparecer.",
        },
        liveMessageFadeOutTimeMs: {
          label: "Tempo de fade das mensagens ao vivo",
          description: "DuraÃ§Ã£o da animaÃ§Ã£o de desaparecimento das mensagens.",
        },
        liveMessageLogFontScale: {
          label: "Escala da fonte das mensagens ao vivo",
          description:
            "Escala as mensagens flutuantes de aÃ§Ã£o a partir do tamanho padrÃ£o.",
        },
        sectionDisplayMinimap: "Minimapa",
        minimap: {
          label: "Minimapa",
          description: "Mostra ou oculta o minimapa da masmorra.",
        },
        minimapScale: {
          label: "Escala do minimapa",
          description: "Escala o tamanho do minimapa a partir do padrÃ£o.",
        },
        sectionDisplayInventory: "ApresentaÃ§Ã£o do inventÃ¡rio",
        reduceInventoryMotion: {
          label: "Reduzir movimento do inventÃ¡rio",
          description:
            "Desativa a expansÃ£o animada das linhas do inventÃ¡rio e usa interaÃ§Ãµes mais simples.",
        },
        inventoryTileOnlyMotion: {
          label: "Animar apenas os tiles do inventÃ¡rio",
          description:
            "Anima os Ã­cones dos tiles enquanto mantÃ©m altura e espaÃ§amento das linhas fixos.",
        },
        inventoryFixedTileSize: {
          label: "Tamanho fixo dos tiles do inventÃ¡rio",
          description:
            "Aplica-se apenas quando Reduzir movimento do inventÃ¡rio estiver ativado. Escolha um tamanho fixo para os Ã­cones.",
          options: {
            none: "Nenhum",
            small: "Pequeno",
            medium: "MÃ©dio",
            large: "Grande",
          },
        },
        groupSound: "Som",
        soundEnabled: {
          label: "Ativar som",
          description:
            "Liga ou desliga o Ã¡udio FMOD. Desativar reduz o processamento de Ã¡udio em dispositivos mais fracos.",
        },
        groupMobileControls: "Controles mÃ³veis",
        invertTouchPanningDirection: {
          label: "Inverter direção do deslocamento",
          description: "Inverte a direção do arrasto para mover a câmera após iniciar o gesto de segurar para mover.",
        },
        groupCombat: "Feedback de combate",
        damageNumbers: {
          label: "NÃºmeros de dano",
          description: "Mostra nÃºmeros flutuantes de dano e cura.",
        },
        displayStatChangesAbovePlayer: {
          label: "Mostrar mudanÃ§as de atributos acima do jogador",
          description:
            "Mostra rÃ³tulos flutuantes para mudanÃ§as de atributos como ForÃ§a e CA.",
        },
        displayXpGainsAbovePlayer: {
          label: "Mostrar ganhos de XP acima do jogador",
          description:
            "Mostra rÃ³tulos flutuantes de XP quando a experiÃªncia aumenta.",
        },
        tileShakeOnHit: {
          label: "Tremor do tile ao acertar",
          description: "Sacode os tiles de impacto quando golpes acertam.",
        },
        sectionCombatBlood: "Efeitos de sangue",
        blood: {
          label: "Sangue",
          description: "Renderiza efeitos de nÃ©voa de sangue nos impactos.",
        },
        bloodMist: {
          label: "NÃ©voa de sangue",
          description:
            "Renderiza partÃ­culas de nÃ©voa de sangue suspensas nos impactos.",
        },
        bloodGround: {
          label: "Respingos de sangue",
          description:
            "Renderiza respingos de sangue no chÃ£o da masmorra apÃ³s impactos.",
        },
        bloodStrength: {
          label: "Intensidade do sangue",
          description:
            "Controla a intensidade visual das texturas e da coloraÃ§Ã£o do sangue.",
        },
        bloodDetail: {
          label: "Detalhe do sangue",
          description:
            "Escolhe a resoluÃ§Ã£o da textura de manchas de sangue por tile da masmorra.",
          options: {
            veryLow: "Muito baixo",
            low: "Baixo",
            medium: "MÃ©dio",
            high: "Alto",
          },
        },
        bloodColorLightHex: {
          label: "Tonalidade clara do sangue no chÃ£o",
          description:
            "Escolhe a tonalidade mais clara usada em manchas frescas de sangue no chÃ£o.",
        },
        bloodColorDarkHex: {
          label: "Tonalidade escura do sangue no chÃ£o",
          description:
            "Escolhe a tonalidade mais escura usada em Ã¡reas densas de sangue no chÃ£o.",
        },
        bloodMistColorHex: {
          label: "Tonalidade da nÃ©voa de sangue",
          description:
            "Escolhe a tonalidade base usada na nÃ©voa de sangue no ar.",
        },
        monsterShatter: {
          label: "EstilhaÃ§ar monstros",
          description:
            "Divide billboards de monstros derrotados em fragmentos fÃ­sicos.",
        },
        monsterShatterBloodBorders: {
          label: "Bordas sangrentas nos estilhaÃ§os",
          description:
            "Tinge pixels prÃ³ximos Ã s linhas de divisÃ£o com bordas vermelho-sangue aleatÃ³rias.",
        },
        groupCompatibility: "Compatibilidade de runtime",
        darkCorridorWalls367: {
          label: "Paredes escuras de corredor legadas",
          description:
            "Infere e armazena em cache tiles de paredes de corredor escuro para runtimes legados do NetHack 3.4.3/3.6.x, incluindo Slash'EM.",
        },
        overrideNh37DarkCorridorWallTiles: {
          label: "Substituir tiles de paredes escuras do NetHack 3.7",
          description:
            "Aplica configuraÃ§Ãµes de substituiÃ§Ã£o de paredes escuras aos tiles de corredor escuro do NetHack 3.7.",
        },
        darkCorridorWallTileOverrideEnabled: {
          label: "Substituir tile de parede escura",
          description:
            "Usa um tile personalizado do atlas para paredes escuras, salvo por tileset.",
        },
        darkCorridorWallSolidColorOverrideEnabled: {
          label: "Usar cor sÃ³lida para paredes escuras",
          description:
            "Usa uma cor RGB escolhida em vez de um tile do tileset.",
        },
      },
      tabs: {
        display: {
          label: "ExibiÃ§Ã£o",
          description: "ConfiguraÃ§Ãµes de interface e exibiÃ§Ã£o.",
        },
        mobile: {
          label: "Celular",
          description: "ConfiguraÃ§Ãµes de toque para jogar no celular.",
        },
        controls: {
          label: "Controles",
          description: "Mapeamentos do controle, modo FPS e comportamento de visÃ£o.",
        },
        sound: {
          label: "Som",
          description: "SaÃ­da de Ã¡udio e controles de som relacionados ao desempenho.",
        },
        combat: {
          label: "Combate",
          description: "Feedback de impacto e resposta visual em combate.",
        },
        compatibility: {
          label: "Compatibilidade",
          description: "Compatibilidade de runtime e alternÃ¢ncias de comportamento do NetHack.",
        },
        updates: {
          label: "AtualizaÃ§Ãµes",
          description:
            "Verifique atualizaÃ§Ãµes online do jogo e revise mudanÃ§as pendentes.",
        },
      },
    },
    update: {
      loading: {
        startupData: "Carregando dados iniciais...",
        tileset: "Carregando conjunto de tiles...",
        runtime: "Iniciando runtime local...",
      },
      runtimeStoppedBeforeStartup:
        "O runtime local do NetHack parou antes de a inicializaÃ§Ã£o terminar.",
      preparingDownload: "Preparando download da atualizaÃ§Ã£o do jogo...",
      idleStatus: "O status da atualizaÃ§Ã£o estÃ¡ ocioso.",
      fileProgress: (index: number, count: number) =>
        `Arquivo ${index} de ${count}`,
      unexpectedCheckFailure: "Falha inesperada ao verificar atualizaÃ§Ã£o.",
      cancelRequested: "Cancelamento solicitado.",
      stoppingActiveDownloadTask: "Interrompendo tarefa de download ativa.",
      unableToCancelDownload:
        "NÃ£o foi possÃ­vel cancelar o download da atualizaÃ§Ã£o.",
      noActiveDownloadToCancel:
        "NÃ£o hÃ¡ download de atualizaÃ§Ã£o ativo para cancelar.",
      startingDownload: "Iniciando download da atualizaÃ§Ã£o do jogo.",
      canceled: "O download da atualizaÃ§Ã£o foi cancelado.",
      unableToDownloadAndApply:
        "NÃ£o foi possÃ­vel baixar e aplicar as atualizaÃ§Ãµes.",
      failed: "A atualizaÃ§Ã£o falhou.",
      latestAlreadyInstalled: "A atualizaÃ§Ã£o mais recente jÃ¡ estÃ¡ instalada.",
      downloadComplete: "Download da atualizaÃ§Ã£o concluÃ­do.",
      nothingAppliedTryAgain:
        "Nenhuma atualizaÃ§Ã£o foi aplicada. Tente verificar novamente.",
      noFilesApplied: "Nenhum arquivo de atualizaÃ§Ã£o foi aplicado.",
      unexpectedFailure: "Falha inesperada na atualizaÃ§Ã£o.",
      checkingForUpdates: "Verificando lanÃ§amentos do GitHub...",
      unsupportedPlatform:
        "NÃ£o Ã© possÃ­vel verificar lanÃ§amentos do GitHub nesta plataforma.",
      latestAlreadyInstalledOptions:
        "VocÃª jÃ¡ tem a versÃ£o mais recente do jogo.",
      oneUpdateAvailable:
        "Uma nova versÃ£o do jogo estÃ¡ disponÃ­vel. Deseja atualizar?",
      manyUpdatesAvailable: (count: number) =>
        `${count} versÃµes mais recentes do jogo estÃ£o disponÃ­veis. Deseja atualizar?`,
      updateCheckFailed: (message: string) =>
        `Falha ao verificar lanÃ§amentos do GitHub: ${message}`,
    },
    saves: {
      sections: {
        manual: "Salvamentos manuais",
        autosave: "Salvamentos automÃ¡ticos",
      },
      deleteTitle: "Excluir jogo salvo?",
      deleteMessage: (name: string) =>
        `Tem certeza de que deseja excluir ${name}?`,
      overwriteTitle: "Sobrescrever jogo salvo?",
      overwriteMessage: (name: string) =>
        `JÃ¡ existe um jogo salvo chamado "${name}". Deseja sobrescrevÃª-lo com um novo personagem?`,
      errorLoading: "Erro ao carregar salvamentos",
      loading: "Carregando salvamentos...",
      noneFound: "Nenhum jogo salvo encontrado.",
      savedAt: (date: string) => `Salvo em: ${date}`,
    },
    tilesets: {
      userTileset: "Tileset do usuÃ¡rio",
      currentSelectionFallback: "este tileset",
      deleteUploadedTitle: "Excluir tileset enviado?",
      deleteUploadedMessage: (label: string) =>
        `Excluir "${label}" dos tilesets enviados?`,
      failedToDelete: "Falha ao excluir tileset.",
      chooseFile: "Escolha um arquivo de tileset PNG/BMP/GIF/JPEG.",
      provideName: "Informe um nome para este tileset.",
      failedToSave: "Falha ao salvar tileset.",
      failedToLoadUploaded: "Falha ao carregar tilesets enviados:",
      userTilesetSuffix: "Tileset do usuÃ¡rio (usuÃ¡rio)",
      noTilesetsFound: "Nenhum tileset encontrado",
      failedToReadImage: "Falha ao ler a imagem do tileset.",
    },
    tilePicker: {
      noAtlasAvailable: "Nenhum atlas de tiles disponÃ­vel.",
      unableToLoadAtlas: "NÃ£o foi possÃ­vel carregar o atlas de tiles.",
      atlasLoaded: "Atlas de tiles carregado.",
      loadingAtlas: "Carregando atlas de tiles...",
      selectedTile: (tileId: number) => `Selecionado: tile #${tileId}`,
      glyph: (label: string) => `Glifo ${label}`,
      tile: (tileId: number) => `Tile ${tileId}`,
      defaultBadge: "PadrÃ£o",
      resetToDefault: "Restaurar padrÃ£o",
      darkWallTitle: "Seletor de tile de parede escura",
      closeDarkWall: "Fechar seletor de tile de parede escura",
      closeBackground: "Fechar seletor de tile de fundo do tileset",
      backgroundHelper:
        "Usado para remover o fundo compartilhado do tileset dos billboards de monstros/saques.",
      backgroundTitle: "Seletor de tile de fundo do tileset",
      backgroundTitleWithLabel: (label: string) =>
        `Seletor de tile de fundo do tileset: ${label}`,
      closeSolidColor: "Fechar seletor de cor sÃ³lida para chroma key",
      solidColorTitle: "Seletor de chroma key de cor sÃ³lida",
      solidColorTitleWithLabel: (label: string) =>
        `Seletor de chroma key de cor sÃ³lida: ${label}`,
    },
    soundPack: {
      discardChangesTitle: "Descartar alteraÃ§Ãµes do pacote de som?",
      discardChangesMessage:
        "Descartar alteraÃ§Ãµes nÃ£o salvas do pacote de som e continuar?",
      discard: "Descartar",
      keepEditing: "Continuar editando",
      failedToLoadIndexedDb: "Falha ao carregar pacotes de som do IndexedDB.",
      failedToSelectRequested:
        "Falha ao selecionar o pacote de som solicitado.",
      provideName: "Informe um nome para o pacote de som.",
      created: (name: string) => `Pacote de som "${name}" criado.`,
      failedToCreate: "Falha ao criar pacote de som.",
      saved: (name: string) => `Pacote de som "${name}" salvo.`,
      failedToSave: "Falha ao salvar pacote de som.",
      failedToExportZip: "Falha ao exportar ZIP do pacote de som.",
      exported: (name: string) => `"${name}" exportado.`,
      failedToImportZip: "Falha ao importar ZIP do pacote de som.",
      imported: (name: string) => `Pacote de som "${name}" importado.`,
      deleteTitle: "Excluir pacote de som?",
      deleteMessage: (name: string) =>
        `Excluir pacote de som "${name}"? Isso nÃ£o pode ser desfeito.`,
      deleted: (name: string) => `Pacote de som "${name}" excluÃ­do.`,
      failedToDelete: "Falha ao excluir pacote de som.",
      noPreviewSource: "Nenhuma fonte de prÃ©via disponÃ­vel para este som.",
      unableToPreview: "NÃ£o foi possÃ­vel reproduzir a prÃ©via deste som.",
      title: "Pacotes de som",
      activePack: "Pacote de som ativo",
      activePackDescription:
        "Selecione o pacote de som ativo usado para resolver caminhos de som.",
      createNew: "Criar novo pacote de som",
      createDescription:
        "Crie um pacote de som personalizado que sobrescreva os padrÃµes.",
      createNameLabel: "Nome do novo pacote de som",
      createPlaceholder: "Meu pacote de som",
      createAndSave: "Criar e salvar",
      packName: "Nome do pacote",
      packNameDescription:
        "Renomeie este pacote e salve para atualizar o namespace dos arquivos de som.",
      savePack: "Salvar pacote de som",
      export: "Exportar pacote de som",
      import: "Importar pacote de som",
      deletePack: "Excluir pacote de som",
      stopPreview: "Parar prÃ©via",
      loading: "Carregando pacotes de som...",
      pendingSaveSuffix: " (salvamento pendente)",
      defaultSuffix: " (padrÃ£o)",
      customSuffix: " (personalizado)",
      noBundledSound: "Sem som embutido",
      enableSoundAria: (label: string) => `Ativar ${label}`,
      volumeAria: (label: string) => `Volume para ${label}`,
      play: "Reproduzir",
      playing: "Reproduzindo...",
      volume: "NÃ­vel do volume",
      remove: "Remover",
      replace: "Substituir",
      soundFile: "Arquivo de som",
      reset: "Redefinir",
      attribution: "AtribuiÃ§Ã£o",
      attributionAria: (label: string) => `AtribuiÃ§Ã£o de ${label}`,
      attributionPlaceholder: "Fonte, criador ou detalhes de licenÃ§a",
      addVariation: "+ Adicionar variaÃ§Ã£o",
    },
    dialogs: {
      pauseMenu: {
        saveBeforeQuit: "Deseja salvar antes de sair?",
        title: "Jogo pausado",
        resume: "Retomar",
        options: "OpÃ§Ãµes",
        saveGame: "Salvar jogo",
        exitToMainMenu: "Voltar ao menu principal",
        quitGame: "Sair do jogo",
      },
      debugLogs: {
        closeLabel: "Fechar logs de depuraÃ§Ã£o",
        title: "Logs de depuraÃ§Ã£o salvos",
        hint: "Os logs sÃ³ sÃ£o capturados depois que o alternador oculto de logs de depuraÃ§Ã£o Ã© ativado.",
        showingEntries: (count: number, startedAt: string) =>
          `Mostrando ${count} registros desde ${startedAt}.`,
        noneSaved: "Ainda nÃ£o hÃ¡ logs de depuraÃ§Ã£o salvos.",
        refresh: "Atualizar",
        clearLogs: "Limpar logs",
      },
      startupUpdate: {
        maintenanceNotice:
          "Nenhum lanÃ§amento mais recente do GitHub foi encontrado.",
        summaryAvailable:
          "Uma nova versÃ£o do jogo estÃ¡ disponÃ­vel. Deseja atualizar?",
        summaryNone:
          "VocÃª jÃ¡ tem a versÃ£o mais recente do jogo.",
        currentVersion: (version: string) => `VersÃ£o atual: ${version}`,
        latestVersion: (version: string) =>
          `Ãšltimo lanÃ§amento do GitHub: ${version}`,
        disableAtStartup:
          "NÃ£o mostrar mais essas notificaÃ§Ãµes ao iniciar.",
        disabledNotice:
          "As notificaÃ§Ãµes de lanÃ§amento ao iniciar agora estÃ£o desativadas. VocÃª pode ativÃ¡-las novamente em OpÃ§Ãµes.",
        clientUpgradeRequired:
          "TambÃ©m Ã© necessÃ¡ria uma atualizaÃ§Ã£o completa do cliente para os aprimoramentos mais recentes da plataforma.",
        progressTitle: "Status do download da atualizaÃ§Ã£o",
        canceling: "Cancelando download da atualizaÃ§Ã£o...",
        noActiveTransfer: "Nenhuma transferÃªncia de arquivo ativa.",
        waitingForUpdater: "Aguardando atividade do atualizador.",
        pendingUpdates: "AtualizaÃ§Ãµes pendentes",
        payloadAvailable: "O pacote da atualizaÃ§Ã£o estÃ¡ disponÃ­vel.",
        downloadUpdates: "Baixar atualizaÃ§Ãµes",
        hideDetails: "Ocultar detalhes",
        moreDetails: "Mais detalhes",
        cancelDownload: "Cancelar download",
      },
      startup: {
        chooseVariant: "Escolha sua variante de NetHack:",
        options: "OpÃ§Ãµes do NetHack 3D",
        quitGame: "Sair do jogo",
        chooseSetup: "Escolha a configuraÃ§Ã£o do seu personagem:",
        randomCharacter: "Personagem aleatÃ³rio",
        createCharacter: "Criar personagem",
        loadGame: "Carregar jogo",
        selectSavedGame: "Selecione um jogo salvo:",
        enterRandomName: "Digite um nome para seu personagem aleatÃ³rio:",
        createCharacterPrompt: "Crie seu personagem:",
        name: "Nome",
        role: "Classe",
        race: "RaÃ§a",
        gender: "GÃªnero",
        alignment: "Alinhamento",
        startGame: "Iniciar jogo",
      },
      clientOptions: {
        closeLabel: "Fechar opÃ§Ãµes do NetHack 3D",
        title: "OpÃ§Ãµes do cliente NetHack 3D",
        categoriesLabel: "Categorias de configuraÃ§Ã£o",
        updates: {
          checkOnLaunchLabel:
            "Mostrar notificaÃ§Ãµes de lanÃ§amentos do GitHub ao iniciar",
          checkOnLaunchDescription:
            "Verifica lanÃ§amentos do GitHub ao iniciar e avisa quando houver uma versÃ£o mais recente.",
          title: "LanÃ§amentos do GitHub",
          description:
            "Compare esta build com os lanÃ§amentos publicados no GitHub.",
          idle:
            "Pressione Verificar atualizaÃ§Ãµes para comparar esta build com os lanÃ§amentos do GitHub.",
          button: "Verificar atualizaÃ§Ãµes",
          openGitHubReleases: "Abrir lanÃ§amentos do GitHub",
        },
        buttons: {
          manageTileSets: "Gerenciar tilesets",
          remapController: "Remapear controle",
          resetControllerDefaults: "Restaurar mapeamentos padrÃ£o do controle",
        },
        hints: {
          darkWallsAlwaysEnabled:
            " Sempre ativado enquanto os tiles de Vulture estiverem ativos.",
          darkWallsDisabledByVulture:
            " Desativado enquanto os tiles de Vulture estiverem ativos.",
          enableDarkWallsFirst:
            " Ative primeiro as paredes escuras de corredor legadas ou as substituiÃ§Ãµes de paredes escuras do NetHack 3.7.",
          enableFpsFirst:
            " Ative primeiro o modo em primeira pessoa em ExibiÃ§Ã£o.",
        },
        darkWallControls: {
          normal: "PadrÃ£o",
          fps: "Modo FPS",
          normalAria: "Cor sÃ³lida da parede escura (modo normal)",
          fpsAria: "Cor sÃ³lida da parede escura (modo FPS)",
          gridLines: "Linhas de grade",
          intensity: "Intensidade",
        },
        controllerRemap: {
          title: "Remapeamento do controle",
          closeLabel: "Fechar remapeamento do controle",
          hint: "Selecione um slot e depois pressione um botÃ£o ou mova um analÃ³gico. Cada aÃ§Ã£o tem dois slots.",
          listeningFor: (label: string, slot: number) =>
            `Aguardando ${label} (slot ${slot}). Pressione ESC para cancelar.`,
        },
        resetPrompt:
          "Restaurar as opÃ§Ãµes do NetHack 3D para os padrÃµes? Seus tilesets personalizados serÃ£o mantidos.",
      },
      tilesetManager: {
        closeLabel: "Fechar gerenciador de tilesets",
        title: "Gerenciar tilesets",
        description:
          "Adicione tilesets e edite configuraÃ§Ãµes de fundo/chroma por tileset.",
        createTitle: "Criar novo tileset",
        editTitle: "Editar tileset",
        editTitleWithName: (label: string) => `Editar tileset: ${label}`,
        tileSetName: "Nome do tileset",
        tileSetPlaceholder: "Meu tileset",
        builtInNamesLocked:
          "Os nomes dos tilesets internos nÃ£o podem ser alterados.",
        tileLayoutVersion: "VersÃ£o do layout dos tiles",
        layout367: "Layout do NetHack 3.6.7",
        layout37: "Layout do NetHack 3.7",
        tileLayoutDescription:
          "Escolha o layout de Ã­ndices de tile usado por este atlas enviado.",
        tileImage: "Imagem do tileset",
        tileImageOptional: "Imagem do tileset (substituiÃ§Ã£o opcional)",
        selectedFile: (fileName: string) => `Selecionado: ${fileName}`,
        currentFile: (fileName: string) => `Atual: ${fileName}`,
        uploadedImage: "imagem enviada",
        backgroundRemovalDescription:
          "Configure a remoÃ§Ã£o de fundo dos billboards para este tileset, ou deixe os dois modos desativados para manter os fundos do atlas intactos.",
        backgroundTileRemoval: "RemoÃ§Ã£o por tile de fundo",
        backgroundTileRemovalDescription:
          "Usa um tile selecionado do atlas para remover o fundo dos billboards.",
        solidChromaKey: "Chroma key de cor sÃ³lida",
        solidChromaKeyDescription:
          "Usa uma Ãºnica cor RGB sÃ³lida para remover o fundo dos billboards.",
        clickToPickFromAtlas: "clique para escolher no atlas",
        saveFirstThenEdit:
          "Salve primeiro o novo tileset e depois edite as configuraÃ§Ãµes de fundo/chroma.",
        createTileSet: "Criar tileset",
        saveTileSet: "Salvar tileset",
        saveTileSettings: "Salvar configuraÃ§Ãµes de tile",
        importNewTileSet: "+ Importar novo tileset",
        noUploadedTilesets: "Nenhum tileset enviado disponÃ­vel.",
        selectedSuffix: " (selecionado)",
        editingSuffix: " (editando)",
        uploadedDetails: (fileName: string, layout: string) =>
          `${fileName} | enviado | layout ${layout}`,
        builtInDetails: (path: string) => `${path} | interno`,
      },
      textInput: {
        cancelLabel: "Cancelar entrada de texto",
        placeholder: "Digite um texto",
        ok: "Confirmar",
      },
      question: {
        cancelPrompt: "Cancelar prompt",
        selectAll: "Selecionar tudo",
        deselectAll: "Desmarcar tudo",
        page: (current: number, total: number) =>
          `PÃ¡gina ${current} / ${total}`,
        pageHintMultiple:
          "Use < e > para trocar de pÃ¡gina. Pressione ESC para cancelar",
        pageHintSingle: "Pressione ESC para cancelar",
        choices: {
          leftRingFinger: "Dedo anelar esquerdo",
          rightRingFinger: "Dedo anelar direito",
          here: "Aqui",
          onGround: "No chÃ£o",
          eligibleItems: "Itens vÃ¡lidos",
          allInventory: "InventÃ¡rio completo",
        },
      },
      runtimeStartError: {
        closeLabel: "Voltar ao menu principal",
        title: "Falha ao inicializar o NetHack.",
        returnToMainMenu: "Voltar ao menu principal",
      },
      newGamePrompt: {
        closeLabel: "Fechar prompt de novo jogo",
        title: "Voltar ao menu principal?",
        reasonFallback: "Fim de jogo",
      },
      direction: {
        cancelLabel: "Cancelar prompt de direÃ§Ã£o",
      },
      info: {
        closeCharacter: "Fechar janela do personagem",
        closeInformation: "Fechar janela de informaÃ§Ãµes",
        characterTitle: "Personagem",
        experienceProgress: "Progresso de experiÃªncia",
        levelLabel: (level: number) => `NÃ­vel ${level}`,
        xpAtMaxLevel: (xp: string) => `XP ${xp} (nÃ­vel mÃ¡ximo alcanÃ§ado)`,
        xpToNextLevel: (xp: string, next: string, remaining: string) =>
          `XP ${xp} / ${next} â€¢ faltam ${remaining} para o prÃ³ximo nÃ­vel`,
        vitals: "Vitais",
        characteristics: "CaracterÃ­sticas",
        currentLimit: "Atual / Limite",
        armorClass: "Classe de armadura",
        currentStatus: "Estado atual",
        noActiveStatus: "Nenhum estado ativo.",
        currentAttributes: "Atributos atuais",
        noTemporaryAttributes: "Nenhum efeito temporÃ¡rio de atributo.",
        characterActions: "AÃ§Ãµes do personagem",
        inventory: "InventÃ¡rio",
        inventoryDetail: "Abrir itens carregados",
        closeHint:
          "Pressione ESPAÃ‡O, ENTER ou ESC para fechar. Pressione Ctrl+M para reabrir.",
        infoTitleFallback: "InformaÃ§Ãµes do NetHack",
        noDetails: "(Sem detalhes)",
      },
      inventory: {
        closeLabel: "Fechar inventÃ¡rio",
        title: "INVENTÃRIO",
        empty: "Seu inventÃ¡rio estÃ¡ vazio.",
        unknownItem: "Item desconhecido",
        closeHint: "Pressione ENTER, ESC ou 'i' para fechar.",
        closeHintWithContext:
          "Selecione um item para abrir comandos contextuais. Pressione ENTER, ESC ou 'i' para fechar",
      },
      inventoryDropMenu: {
        title: "Largar",
        dropType: "Tipo de descarte",
        dropAmount: "Quantidade a largar",
        dropSpecificAmount: "Largar uma quantidade especÃ­fica",
        onlyStackedItems: "DisponÃ­vel apenas para itens empilhados",
      },
      inventoryDropCount: {
        title: "Quantos desta pilha deseja largar?",
        chooseAmount: (max: number) =>
          `Escolha uma quantidade entre 1 e ${max}.`,
        ariaLabel: "Quantidade a largar",
        setMinimum: "Definir a quantidade mÃ­nima para largar",
        decrease: "Diminuir a quantidade em um",
        increase: "Aumentar a quantidade em um",
        setMaximum: "Definir a quantidade mÃ¡xima para largar",
      },
      mobileActions: {
        extendedCommands: "Comandos estendidos",
        commonCommands: "Comandos comuns",
        allCommands: "Todos os comandos",
        actions: "AÃ§Ãµes",
        menu: "Menu geral",
        close: "Fechar",
        wizardCommands: "Comandos de assistente",
        wizard: "Assistente",
        repeat: "Repetir",
        character: "Personagem",
        inventory: "InventÃ¡rio",
        log: "Registro",
        pickUp: "Pegar",
        search: "Procurar",
        closeMessageLog: "Fechar registro de mensagens",
      },
      positionPrompt: {
        closeLabel: "Fechar prompt de posiÃ§Ã£o",
      },
      controllerSupport: {
        prompt: "Controle detectado. Ativar suporte a controle?",
      },
    },
  },
} satisfies LocaleOverrides<TranslationDictionary>;
