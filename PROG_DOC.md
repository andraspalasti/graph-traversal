# Programozói dokumentáció

## A projekt struktúra

- **hash_tables** Különböző hash táblák amelyek különböző típusú adatot tudnak tárolni

  - **hash_table_b** bool típusú hash tábla
  - **hash_table_d** double típusú hash tábla
  - **hash_table** olyan hash tábla aminek az adat mezője egy `void *` tehát bármilyen típusú pointert tud tárolni

- **visualization** Olyan fájlokat tartalmaz amely az `SDL`-hez vagy az alakzatok kirajzolásához kapcsolódik

  - **animations** Az animációkkal kapcsolatos fügvényeket tartalmazza
  - **draw** Az alakzatok rajzolásához kapcsolatos függvényeket tartalmazza
  - **sdl_helpers** Az SDL inicializálásához kapcsolatos függvényeket tartalmazza
  - **visualization**

- **console_menu** A konzolon való belvasás és kirajzoláshoz kapcsolatos függvényeket tartalmazza

- **coordinates** Tartalmazza a coordináta struktúrát és a koordinátákat manipuláló függvényeket

- **file_managment** A fájlok beolvasásával és mentésével kapcsolatos függvényeket tartalmazza

- **graph** Tartalmazza a gráf struktúrát valamint a a gráf módosításához kapcsolatos függvényeket

- **list_node** Tartalmazza a `list_node` láncolt lista struktúrát valamint a módosításával kapcsolatos függvényeket

- **node** Tartalmazz a `Node` struktúrát és a manipulálásával kapcsolatos függvényeket

- **path_finding** Tartalmazz az algoritmust ami segítségével meg tudjuk mondani a legrövidebb utat két csúcs közöttt

- **queue** Tartalmazz a `queue` adatszerkezet megvalósítását

- **util** Olyan függvényeket tartalmaz nem besorolható egy specifikus modulba sem

---

## `hash_tables`

Ez a mappa a különböző típusú hash táblákat tartalmazz itt csak a `hash_table.[c|h]` fájl struktúráit fogom részletezni mivel a többi hash tábla csak típusokban tér el ettől.

**Struktúrák:**

```c
typedef struct Record {
    char *key; /* Az adat kulcsa ami alapján lehet keresni a táblában */
    void *val; /* Az adat amit a rekord tárol */
    struct Record *next;
} Record;

typedef struct HashTable {
    int size; /* A rekordok száma */
    struct Record **records; /* rekordok */

    /* Azért használok itt function pointereket mert több hash táblám is van és  nem akarom hogy az név ütközések legyenek */

    /* Megkeresi a hash táblában az adott kulcshoz tartozó adatot
    ha megtalálta visszaadja azt
    ha nem akkor NULL pointert ad vissza */
    void **(*get)(const struct HashTable *, const char *);

    /* Az adott kulcshoz tartozó adatot felülírja vagy ha a kulcs még nincs a táblában akkor beleteszi */
    void (*set)(struct HashTable *, char *, void *);

    /* Felszabadítja a hash tábla által lefoglalt memóriát */
    void (*ht_free)(struct HashTable *);
} HashTable;
```

**Függvények:**

Példányosít egy hash tábla struktúrát az alap értékekkel és visszaadja a rá mutató pointert. A `size` paraméter a hash tábla rekordjainak a számát határozza meg.

```c
HashTable *init_ht(int size);
```

Ha megtalálja a kulcsot a hash táblában akkor felülírja a hozzá tartozó adatot ha nem akkor beilleszti.

```c
static void set_value(HashTable *self, char *key, void *val);
```

Megkeresi a paraméterként átadott kulcsot a paraméterként átadott hash táblában
ha megtalálta akkor visszaadja a pointert a rá mutató adatra
ha nem akkor NULL pointert ad vissza

```c
static void **get_value(const HashTable *self, const char *key);
```

Felszabadítja a hash tábla által lefoglalt memóriát

```c
static void free_ht(HashTable *self);
```

Példányosít egy rekordot aminek a kulcsa a `key` paraméter és az értéke pedig a `val` paraméter lesz. A rekordra mutató pointert adja vissza.

```c
static Record *init_record(char *key, void *val);
```

Felszabadítja a rekord által lefoglalt memóriát

```c
static void free_record(Record *r);
```

---

## `animations`

**Struktúrák:**

```c
typedef struct Animation {
    Uint64 START_TIME;    /* Az animáció kezdetekor az idő */
    double ANIM_DURATION; /* Az animáció futás ideje ms-ben */
    double delta_time;    /* Az eltelt idő az animáció kezdete óta */
    bool is_finished;     /* Akkor igaz ha az animáció befejeződött */
} Animation;
```

**Függvények:**

Példányosít egy animáció struktúrát ekkor kérdezi le az időt és teszi be a
`START_TIME` mezőbe. SDL-t használ hogy megnézze az időt tehát csak ott lehet használni ahol már
példányosítva van az SDL.
Paramétere az animáció hossza ms-ban

```c
Animation *init_animation(double animation_duration);
```

Frissíti az animációt tehát megnézi újra az időt és beteszi ezt az animáció
`delta_time` mezőjébe és az animáció `is_finished` státuszát is frissíti.

```c
void update_animation(Animation *anim);
```

Újra indítja az animációt tehát a következő mezőket resetteli: `is_finished`, `delta_time`, `START_TIME`

```c
void restart_animation(Animation *anim);
```

Felszabadítja az animáció által lefoglalt memóriát

```c
void free_animation(Animation *anim);
```

---

## `draw`

**Struktúrák:** Nincsenek

**Függvények:**

A paraméterként átadott gráfot rajzolja ki a `renderer`-re a `font` segítségével.

```c
void draw_graph(SDL_Renderer *renderer, TTF_Font *font, const Graph *g) {
```

Rajzol egy egynest ami összeköti a két csúcsot
a `node_radius` itt a csúcsok sugara ez azért kell mivel nem a csúcsok középpontját köti
össze hanem a megrajzolt körök szélét
A `color` paraméter az egyenes színét határozza meg.

```c
void draw_line_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color);
```

Rajzol egy nyilat ami összeköti a két csúcsot. A nyíl az első csúcstól indul a másodikba.
A `color` paraméter a nyíl színét határozza meg.

```c
void draw_arrow_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color);
```

Egy egyenest rajzol amely összeköti a paraméterként kapott koordinátákat.
A `color` paraméter az egyenes színét határozza meg.

```c
void draw_line(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color);
```

Egy nyílat rajzol amely összeköti a paraméterként kapott koordinátákat.
Az első koordinátából indul a nyíl a másodikba.
A `color` paraméter az egyenes színét határozza meg.

```c
void draw_arrow(SDL_Renderer *renderer, Coordinates from, Coordinates to, Uint32 color);
```

Egy csúcsot rajzol. Paraméterek:

- `font` Betűtípust adja meg
- `n` a csúcs amit meg kell rajzolni
- `node_radius` Azt adja meg hogy mekkora sugarú kört rajzoljunk a csúcs középpontja köré

```c
void draw_node(SDL_Renderer *renderer, TTF_Font *font, const Node *n, double node_radius);
```

Módosítja a paraméterként beadott `vector` változót
úgy hogy a két csúcsot összekötő egyenes két végpontjának koordinátája legyen benne.
A `node_radius` itt a csúcsok sugara ez azért kell mivel nem a csúcsok középpontját köti
össze hanem a megrajzolt körök szélét

```c
void get_vector(Coordinates *vector, const Node *n1, const Node *n2, double node_radius);
```

---

## `sdl_helpers`

**Struktúrák:** Nincsenek

**Függvények:**

Példányosít egy `SDL_Window` és egy `SDL_Renderer` struktúrát és felülírja velük a beadott `pwindow` és `prender` paramétereket.
A `width` és `height` paraméterek az SDL ablak méreteit határozzák meg.

```c
void sdl_init(int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer);
```

Beolvassa a `ttf_file` paraméterrel meghatározott ttf fájlt.
A `font_size` paraméter a betűtípus méretét határozza meg.

```c
TTF_Font *ttf_init(const char *ttf_file, int font_size);
```

Az átadott szöveget kirajzolja középre igazítva.
Paraméterei:

- `renderer` A renderer amire kiírja a szöveget
- `font` A betűtípus amit a szöveg kiírásához használ
- `text` A szöveg amit kiír
- `coords` A coordináták ahova kiíródjon a szöveg

```c
void render_text(SDL_Renderer *renderer, TTF_Font *font, Uint32 color, const char *text, Coordinates coords);
```

Egy `SDL_Color` struktúrát ad vissza amit a `color` paraméterből állít elő

```c
SDL_Color hexcolor_to_sdl_color(Uint32 color);
```

---

## `visualization`

**Struktúrák:** Nincsnek

**Globális változók:**

```c
BG_COLOR           /* Az SDL ablak hátterének színe*/
TEXT_COLOR         /* A szöveg színe */
EDGE_COLOR         /* A gráfban a csúcsokat összekötő élek színe */
NODE_BORDER_COLOR  /* A csúcs körvonalának a színe */
NODE_COLOR         /* Egy csúcs háttérszíne */
PATH_COLOR         /* Az útvonal rajzolásnál az útvonal színe */

SCREEN_HEIGHT      /* Az SDL ablak magassága */
SCREEN_WIDTH       /* Az SDL ablak szélessége */
NODE_RADIUS        /* Egy csúcs sugara */
MARGIN             /* Az SDL ablak széle körüli margó */
ARROW_HEAD_LENGTH  /* A nyíl hegyének a hossza */
ARROW_HEAD_WIDTH   /* A nyíl hegyének a szélessége */

/* Az x koordináta maximum megengedett értéke */
#define MAX_X_COORD (SCREEN_WIDTH - NODE_RADIUS - MARGIN) / 2

/* Az y koordináta maximum megengedett értéke */
#define MAX_Y_COORD (SCREEN_HEIGHT - NODE_RADIUS - MARGIN) / 2
```

**Függvények:**

Nyit egy SDL ablakot majd elkezdi animálni a gráf megrajzolását.

```c
void display_graph(Graph *g);
```

Nyit egy SDL ablakot majd elkezdi animálni a gráf megrajzolását.

```c
void display_graph(Graph *g);
```

Nyit egy SDL ablakot, kirajzolja a gráfot majd a paraméterként átadott útvonalat elkezdi animálni.

```c
void display_graph_with_path(Graph *g, Path *p);
```

---

## `console_menu`

**Struktúrák:** Nincsenek

```c
TIME_TO_READ_MSG /* Az idő amíg egy visszajelző üzenet el nem tűnik násodpercben */

/* A lehetséges menü státuszok */
enum MenuState {
    QUIT = -2,
    IDLE = -1,
    LOAD_GRAPH = 0,
    SAVE_GRAPH = 1,
    ADD_NODE = 2,
    REMOVE_NODE = 3,
    ADD_EDGE = 4,
    REMOVE_EDGE = 5,
    DISPLAY_GRAPH = 6,
    DISPLAY_GRAPH_WITH_PATH = 7,
};
```

**Függvények:**

Előkészít a konzolon egy olyan környzetet ahol tudunk választani a menükből a fel/le nyilakkal.
Valamint visszaadja a kiválasztott menüt. Ha a felhasználó `escape`-t nyom akkor `QUIT` státuszt fog vissza adni.
A `menu_items` paraméterekkel pedig azt mondhatjuk meg hogy az adott `MenuState`-hez milyen szöveget írjon ki.

```c
enum MenuState select_menu(const char *menu_items[]);
```

A konzolon keresztül kér a felhasználótól egy fájl útvonalat.
Majd megpróbálja beolvasni a fájlt mint gráf.
A beolvasott fájlt a paraméterként megadott gráfba tölti bele.

```c
enum MenuState load_graph_menu(Graph *g);
```

A konzolon keresztül kér a felhasználótól egy fájl útvonalat.
Majd megpróbálja a paraméterként megaadott gráfot elmenteni a fájlba.

```c
enum MenuState save_graph_menu(const Graph *g);
```

Addig kéri a felhasználótól egy csúcs nevét a konzolon keresztül amíg meg nem tudja találni azt a paraméterként átadott gráfban.

```c
Node *find_node_from_console(const Graph *g);
```

Egy csúcsot hoz létre úgy hogy a csúcs nevét és koordinátáit a konzolról olvassa be. Visszaadja az új csúcsra mutató pointert.

```c
Node *read_node_from_console();
```

---

## `coordinates`

**Struktúrák:**

Egy koordináta struktúra amely egy pont x és y koordinátáit tartalmazza.

```c
typedef struct Coordinates {
    double x, y;
} Coordinates;
```

**Függvények:**

A paraméterként megadott koordinátát formázva kiírja a konzolra.

```c
void print_coords(Coordinates coords);
```

Visszaadja a paraméterként beadott két koordináta közötti távolságot.

```c
double distance(Coordinates a, Coordinates b);
```

Visszaadja a paraméterként megadott koordináta SDL beli megfelelőjét a `width` és a `height` paraméterek alapján.

```c
Coordinates normalize_coords(Coordinates coords, int width, int height);
```

Beszorozza a paraméterként átadott koordinátákat `lambda` értékével majd az így kapott koordinátákat vissza adja.

```c
Coordinates scale(double lambda, Coordinates coords);
```

Az `origin` koordináta körül megfordítja a `coords` koordinátát `alpha` szöggel.

```c
Coordinates rotate_around(Coordinates origin, Coordinates coords, double alpha);
```

Két koordinátát össze ad és az eredményt vissza adja.

```c
Coordinates add(Coordinates c1, Coordinates c2);
```

A második koordinátát kivonja az elsőből majd az eredményt vissza adja.

```c
Coordinates subtract(Coordinates c1, Coordinates c2);
```

---
