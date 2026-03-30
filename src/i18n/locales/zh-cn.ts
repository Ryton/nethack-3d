import { en, type TranslationDictionary } from "./en";

type DeepPartial<T> = {
  [K in keyof T]?: T[K] extends (...args: any[]) => any
    ? T[K]
    : T[K] extends string
      ? string
      : T[K] extends number
        ? number
        : T[K] extends boolean
          ? boolean
          : T[K] extends bigint
            ? bigint
            : T[K] extends symbol
              ? symbol
              : T[K] extends object
                ? DeepPartial<T[K]>
                : T[K];
};

function isPlainObject(value: unknown): value is Record<string, unknown> {
  return typeof value === "object" && value !== null && !Array.isArray(value);
}

function mergeTranslations<T>(base: T, overrides: DeepPartial<T>): T {
  if (!isPlainObject(base) || !isPlainObject(overrides)) {
    return (overrides as T) ?? base;
  }

  const result: Record<string, unknown> = { ...(base as Record<string, unknown>) };
  for (const [key, overrideValue] of Object.entries(overrides)) {
    if (overrideValue === undefined) {
      continue;
    }

    const baseValue = (base as Record<string, unknown>)[key];
    if (isPlainObject(baseValue) && isPlainObject(overrideValue)) {
      result[key] = mergeTranslations(baseValue, overrideValue as never);
    } else {
      result[key] = overrideValue;
    }
  }

  return result as T;
}

const zhCnOverrides = {
  meta: {
    locale: "zh-CN",
  },
  common: {
    confirm: "确认",
    cancel: "取消",
    close: "关闭",
    back: "返回",
    yes: "是",
    no: "否",
    delete: "删除",
    done: "完成",
    resetToDefaults: "重置为默认值",
    later: "稍后",
    checking: "正在检查...",
    downloading: "正在下载...",
    canceling: "正在取消...",
    none: "无",
    off: "关闭",
    normal: "正常",
    fps: "帧率",
  },
  controller: {
    groups: {
      movement: "移动",
      lookAndCamera: "观察与镜头",
      actions: "操作",
      dialogs: "对话框",
      system: "系统",
    },
    actions: {
      dpad_up: { label: "方向键上", description: "在对话框和移动预览中向上导航。" },
      dpad_down: { label: "方向键下", description: "在对话框和移动预览中向下导航。" },
      dpad_left: { label: "方向键左", description: "在对话框和移动预览中向左导航。" },
      dpad_right: { label: "方向键右", description: "在对话框和移动预览中向右导航。" },
      left_stick_up: { label: "左摇杆上", description: "移动预览和虚拟光标向上。" },
      left_stick_down: { label: "左摇杆下", description: "移动预览和虚拟光标向下。" },
      left_stick_left: { label: "左摇杆左", description: "移动预览和虚拟光标向左。" },
      left_stick_right: { label: "左摇杆右", description: "移动预览和虚拟光标向右。" },
      right_stick_up: { label: "右摇杆上", description: "观察、镜头平移以及对话框向上滚动。" },
      right_stick_down: { label: "右摇杆下", description: "观察、镜头平移以及对话框向下滚动。" },
      right_stick_left: { label: "右摇杆左", description: "向左观察和镜头平移。" },
      right_stick_right: { label: "右摇杆右", description: "向右观察和镜头平移。" },
      confirm: { label: "确认 / 点击", description: "确认移动并在对话框中点击。" },
      search: { label: "搜索", description: "当没有活动的移动预览时搜索当前格子。" },
      cancel_or_context: { label: "取消 / 上下文", description: "打开上下文操作或取消当前对话框。" },
      action_menu: { label: "操作菜单", description: "打开控制器径向操作菜单。" },
      run_modifier: { label: "跑步修饰键", description: "按住后在移动前发送跑步前缀。" },
      zoom_in: { label: "缩放（按住）", description: "按住后使用左或右摇杆上下缩放。" },
      recenter_camera: { label: "镜头居中", description: "将镜头返回到玩家中心。" },
      toggle_large_minimap: { label: "切换大型小地图", description: "切换超大尺寸小地图。" },
      pause_menu: { label: "暂停菜单", description: "打开或关闭暂停菜单。" },
      open_inventory: { label: "物品栏", description: "打开物品栏窗口。" },
      open_character: { label: "角色卡", description: "打开角色卡窗口。" },
    },
    listening: "请按下输入...",
    clear: "清除",
    controllerDetected: (count: number) => `检测到 ${count} 个控制器。`,
    noControllerDetected: "未检测到控制器。",
  },
  startupInitOptions: {
    accordion: {
      summary: "初始化选项（可选）",
      description:
        "启动时应用的额外 NetHack `OPTIONS` 条目。刻意省略了窗口端口和平台专用选项。",
      resetToDefaults: "重置为默认值",
    },
    options: {
      playmode: {
        label: "游戏模式",
        description:
          "选择启动模式。巫师模式是 NetHack 调试模式（`playmode:debug`）。",
        options: { normal: "正常", explore: "探索", debug: "巫师/调试" },
      },
      autopickup: { label: "自动拾取", description: "自动拾取在拾取类型中选中的物品类别。" },
      pickup_types: {
        label: "拾取类型",
        description: "自动拾取的物品类别符号（例如：$\"=/!?+）。留空则使用游戏默认值。",
        placeholder: '$"=/!?+',
      },
      pickup_thrown: { label: "拾取投掷物", description: "当投掷物落地时自动拾取。" },
      pickup_burden: {
        label: "拾取负重阈值",
        description: "当拾取会超过该负重等级时先提示确认。",
        options: {
          u: "未负重 (u)",
          b: "负重 (b)",
          s: "吃力 (s)",
          n: "紧张 (n)",
          t: "过载 (t)",
          l: "超载 (l)",
        },
      },
      autoopen: { label: "自动开门", description: "朝门移动时自动尝试打开门。" },
      autodig: { label: "自动挖掘", description: "当可挖掘且朝墙移动时自动挖掘。" },
      cmdassist: { label: "命令辅助", description: "命令输入错误时显示额外帮助文本。" },
      confirm: { label: "确认攻击", description: "在攻击友好生物前询问。" },
      safe_pet: { label: "保护宠物", description: "在可能打到宠物前询问。" },
      help: { label: "游戏内帮助", description: "当存在更多信息时，提示显示额外的观察/帮助细节。" },
      legacy: { label: "传统开场", description: "新游戏开始时显示故事开场。" },
      rest_on_space: { label: "空格休息", description: "将空格键视为等待/休息。" },
      extmenu: { label: "扩展命令菜单", description: "为扩展命令使用菜单弹窗。" },
      fixinv: { label: "固定物品栏字母", description: "物品移动时尽量保留物品栏字母。" },
      implicit_uncursed: { label: "显示未诅咒", description: "在物品描述中始终包含“未诅咒”字样。" },
      sortloot: {
        label: "整理拾取列表",
        description: "拾取与物品选择列表的排序方式。",
        options: { f: "完整", l: "仅拾取", n: "无" },
      },
      sortpack: { label: "整理物品栏", description: "显示物品栏时按类型排序包内物品。" },
      msghistory: { label: "消息历史大小", description: "保留用于回看的一行消息数量。" },
      pile_limit: { label: "堆叠上限", description: "触发地面物品弹窗列表的物品数量阈值。" },
      autoquiver: { label: "自动装填弩袋", description: "射击时自动填充弩袋或准备合适的武器。" },
      pushweapon: { label: "推移武器", description: "切换武器时将当前持用武器移到副手。" },
      mention_walls: { label: "提示墙壁", description: "朝墙移动时显示一条消息。" },
      dogname: { label: "小狗名字", description: "你的第一只小狗的默认名字。", placeholder: "Fido" },
      catname: { label: "小猫名字", description: "你的第一只小猫的默认名字。", placeholder: "Morris" },
      horsename: { label: "马名字", description: "你的第一匹马的默认名字。", placeholder: "Silver" },
      pettype: {
        label: "偏好的宠物",
        description: "可变角色的初始宠物类型偏好。",
        options: { default: "游戏默认", cat: "猫", dog: "狗", horse: "马", none: "无" },
      },
      fruit: { label: "偏好的水果", description: "角色喜欢的水果类型名称。" },
      packorder: { label: "物品栏顺序", description: "物品栏中显示的物品类别顺序。" },
      paranoid_confirmation: {
        label: "高警惕确认",
        description: "以空格分隔的额外确认项（例如：confirm quit attack pray）。",
      },
      sparkle: { label: "魔抗闪光", description: "显示魔法抗性特效闪光。" },
      standout: { label: "突出显示怪物/更多", description: "将怪物和 --More-- 提示加粗显示。" },
      tombstone: { label: "墓碑", description: "死亡时显示墓碑图像。" },
      verbose: { label: "详细消息", description: "使用更完整的状态和动作消息措辞。" },
    },
  },
  soundEffects: {
    byKey: {
      "player-walk": "玩家行走",
      hit: "命中",
      "monster-killed": "怪物被击杀（玩家）",
      "monster-killed-other": "怪物被击杀（其他）",
      "missed-attack": "攻击未命中",
      "door-opens": "门打开",
      "door-closes": "门关闭",
      "door-kick": "踢门",
      "door-smash": "撞门",
      "door-resists": "门抵抗",
      "door-distant": "远处的门",
      "walk-down-stairs": "走下楼梯",
      "walk-up-stairs": "走上楼梯",
      eating: "进食",
      drink: "饮用",
      "quaff-potion": "猛灌药水",
      "pickup-gold": "拾取金币",
      "pickup-item": "拾取物品",
      "find-hidden": "发现隐藏门/通道",
      "level-up": "升级",
      unlock: "解锁",
      "boulder-push": "推动巨石",
      "boulder-blocked": "巨石被阻挡",
      splash: "溅落",
      searching: "搜索",
      "magic-cast": "施法",
      "magic-heal": "治疗魔法",
      "magic-buff": "增益魔法",
    },
  },
  characterSheet: {
    titleFallback: "角色卡",
    sectionTitles: {
      overview: "概览",
      background: "背景",
      basics: "基础信息",
      characteristics: "当前特性",
      status: "当前状态",
      attributes: "当前属性",
    },
    statLabels: {
      strength: "力量",
      dexterity: "敏捷",
      constitution: "体质",
      intelligence: "智力",
      wisdom: "感知",
      charisma: "魅力",
    },
    commands: {
      enhance: { label: "提升", detail: "提升技能等级" },
      conduct: { label: "行为记录", detail: "显示挑战进度" },
      overview: { label: "概览", detail: "显示地牢进度" },
      spells: { label: "法术", detail: "查看已知法术" },
      seespells: { label: "法术书", detail: "列出法术库存" },
      known: { label: "已知发现", detail: "已知物品列表" },
      pray: { label: "祈祷", detail: "尝试祈祷" },
    },
  },
  castMenu: {
    schoolLabel: "学派：",
    headings: { name: "名称", level: "等级", category: "类别", fail: "失败率", retention: "保留度" },
    summary: {
      known: (count: number) => `已知 ${count} 个`,
      castable: (count: number) => `可施法 ${count} 个`,
      bestSuccess: (percent: number) => `最佳成功率 ${percent}%`,
      averageFail: (percent: number) => `平均失败率 ${percent}%`,
      schoolCount: (count: number) => `${count} 个学派`,
    },
    retention: { unknown: "未知", gone: "消失", full: "100%" },
  },
  enhanceMenu: {
    defaultGroupTitle: "技能",
    availability: {
      available_now: "可用",
      needs_experience: "经验/槽位",
      needs_practice: "需练习",
      maxed_out: "已满",
    },
    summary: {
      available: (count: number) => `${count} 项可用`,
      gated: (count: number) => `${count} 项受经验/槽位限制`,
      practice: (count: number) => `${count} 项需要练习`,
      maxed: (count: number) => `${count} 项已满`,
    },
    maxLabel: "最大",
    slotCount: (count: number) => `${count} 个槽位`,
  },
  app: {
    unknownTime: "未知时间",
    debugSession: { possibleCrash: "可能崩溃", active: "活动中" },
    characterStats: {
      descriptions: {
        strength: "影响近战伤害、负重能力和强制动作。",
        dexterity: "影响命中率、陷阱互动和防御灵活性。",
        constitution: "影响生命值成长以及对毒素和吸能效果的抗性。",
        intelligence: "影响阅读，以及许多法术相关动作的成功率。",
        wisdom: "影响法力成长和施法可靠性。",
        charisma: "影响商店互动、宠物管理和社交结果。",
      },
      armorClassDescription: "数值越低越好。护甲等级会降低敌人命中你的几率。",
    },
    directionHelp: {
      controller:
        "点击一个方向，或使用左摇杆/方向键预览并松开确认。中心圆圈以自身为目标。使用 < 或 > 走楼梯。按 ESC 取消。",
      numpad:
        "点击一个方向。中心圆圈以自身为目标。你也可以使用小键盘（1-4、6-9）、方向键、<、> 或 s。按 ESC 取消。",
      viKeys:
        "点击一个方向。中心圆圈以自身为目标。你也可以使用 hjkl/yubn、方向键、<、> 或 s。按 ESC 取消。",
      fps: "对准目标。左键或 W 确认。S 以自身为目标。A/D 或右键取消。",
    },
    update: {
      loading: {
        startupData: "正在加载启动数据...",
        tileset: "正在加载瓦片集...",
        runtime: "正在启动本地运行时...",
      },
      runtimeStoppedBeforeStartup: "本地 NetHack 运行时在启动完成前停止了。",
      checkingForUpdates: "正在检查更新...",
      unsupportedPlatform: "此平台不支持在线游戏更新。",
      oneUpdateAvailable: "有 1 个游戏更新可用。",
      manyUpdatesAvailable: (count: number) => `有 ${count} 个游戏更新可用。`,
      updateCheckFailed: (message: string) => `更新检查失败：${message}`,
    },
    saves: {
      sections: { manual: "手动存档", autosave: "自动存档" },
      deleteTitle: "删除已保存游戏？",
      deleteMessage: (name: string) => `你确定要删除 ${name} 吗？`,
      overwriteTitle: "覆盖已保存游戏？",
      overwriteMessage: (name: string) =>
        `名为“${name}”的已保存游戏已存在。要用新角色覆盖它吗？`,
      noneFound: "未找到已保存的游戏。",
    },
    tilesets: {
      chooseFile: "选择一个 PNG/BMP/GIF/JPEG 瓦片集文件。",
      provideName: "为此瓦片集提供一个名称。",
      noTilesetsFound: "未找到瓦片集",
    },
    dialogs: {
      pauseMenu: {
        saveBeforeQuit: "退出前要保存吗？",
        title: "游戏已暂停",
        resume: "继续",
        options: "选项",
        saveGame: "保存游戏",
        exitToMainMenu: "返回主菜单",
        quitGame: "退出游戏",
      },
      startup: {
        chooseVariant: "选择你的 NetHack 变体：",
        options: "NetHack 3D 选项",
        quitGame: "退出游戏",
        chooseSetup: "选择你的角色配置：",
        randomCharacter: "随机角色",
        createCharacter: "创建角色",
        loadGame: "加载游戏",
        selectSavedGame: "选择一个已保存的游戏：",
        enterRandomName: "为你的随机角色输入名字：",
        createCharacterPrompt: "创建你的角色：",
        name: "名字",
        role: "职业",
        race: "种族",
        gender: "性别",
        alignment: "阵营",
        startGame: "开始游戏",
      },
      info: {
        closeCharacter: "关闭角色窗口",
        closeInformation: "关闭信息窗口",
        characterTitle: "角色",
        experienceProgress: "经验进度",
        levelLabel: (level: number) => `等级 ${level}`,
        vitals: "生命状态",
        characteristics: "特性",
        armorClass: "护甲等级",
        currentStatus: "当前状态",
        currentAttributes: "当前属性",
        characterActions: "角色操作",
        inventory: "物品栏",
        inventoryDetail: "打开携带物品",
        closeHint: "按 SPACE、ENTER 或 ESC 关闭。按 Ctrl+M 重新打开。",
      },
      inventory: {
        closeLabel: "关闭物品栏",
        title: "物品栏",
        empty: "你的物品栏是空的。",
        unknownItem: "未知物品",
        closeHint: "按 ENTER、ESC 或 `i` 关闭。",
      },
      controllerSupport: {
        prompt: "检测到控制器。要启用控制器支持吗？",
      },
    },
  },
} satisfies DeepPartial<TranslationDictionary>;

export const zhCn = mergeTranslations(en, zhCnOverrides);
