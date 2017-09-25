#include <map>
#include <cstring>
#include <algorithm>

#include "emoji.h"

using namespace std;

namespace emoji {

    typedef map<wstring, wstring> Emojis;

    static Emojis emojis = {
            {L"✈", L"AIRPLANE"},
            {L"⏰", L"ALARM CLOCK"},
            {L"👾", L"ALIEN MONSTER"},
            {L"🚑", L"AMBULANCE"},
            {L"🏈", L"AMERICAN FOOTBALL"},
            {L"⚓", L"ANCHOR"},
            {L"💢", L"ANGER SYMBOL"},
            {L"😠", L"ANGRY FACE"},
            {L"😧", L"ANGUISHED FACE"},
            {L"🐜", L"ANT"},
            {L"📶", L"ANTENNA WITH BARS"},
            {L"🔄", L"ANTICLOCKWISE DOWNWARDS AND UPWARDS OPEN CIRCLE ARROWS"},
            {L"♒", L"AQUARIUS"},
            {L"♈", L"ARIES"},
            {L"⤵", L"ARROW POINTING RIGHTWARDS THEN CURVING DOWNWARDS"},
            {L"⤴", L"ARROW POINTING RIGHTWARDS THEN CURVING UPWARDS"},
            {L"🚛", L"ARTICULATED LORRY"},
            {L"🎨", L"ARTIST PALETTE"},
            {L"😲", L"ASTONISHED FACE"},
            {L"👟", L"ATHLETIC SHOE"},
            {L"🍆", L"AUBERGINE"},
            {L"🏧", L"AUTOMATED TELLER MACHINE"},
            {L"🚗", L"AUTOMOBILE"},
            {L"👶", L"BABY"},
            {L"👼", L"BABY ANGEL"},
            {L"🍼", L"BABY BOTTLE"},
            {L"🐤", L"BABY CHICK"},
            {L"🚼", L"BABY SYMBOL"},
            {L"🔙", L"BACK WITH LEFTWARDS ARROW ABOVE"},
            {L"🐫", L"BACTRIAN CAMEL"},
            {L"🛄", L"BAGGAGE CLAIM"},
            {L"🎈", L"BALLOON"},
            {L"☑", L"BALLOT BOX WITH CHECK"},
            {L"🍌", L"BANANA"},
            {L"🏦", L"BANK"},
            {L"💵", L"BANKNOTE WITH DOLLAR SIGN"},
            {L"💶", L"BANKNOTE WITH EURO SIGN"},
            {L"💷", L"BANKNOTE WITH POUND SIGN"},
            {L"💴", L"BANKNOTE WITH YEN SIGN"},
            {L"📊", L"BAR CHART"},
            {L"💈", L"BARBER POLE"},
            {L"⚾", L"BASEBALL"},
            {L"🏀", L"BASKETBALL AND HOOP"},
            {L"🛀", L"BATH"},
            {L"🛁", L"BATHTUB"},
            {L"🔋", L"BATTERY"},
            {L"🐻", L"BEAR FACE"},
            {L"💓", L"BEATING HEART"},
            {L"🍺", L"BEER MUG"},
            {L"🔔", L"BELL"},
            {L"🔕", L"BELL WITH CANCELLATION STROKE"},
            {L"🍱", L"BENTO BOX"},
            {L"🚲", L"BICYCLE"},
            {L"🚴", L"BICYCLIST"},
            {L"👙", L"BIKINI"},
            {L"🎱", L"BILLIARDS"},
            {L"🐦", L"BIRD"},
            {L"🎂", L"BIRTHDAY CAKE"},
            {L"♣", L"BLACK CLUB SUIT"},
            {L"♦", L"BLACK DIAMOND SUIT"},
            {L"⏬", L"BLACK DOWN-POINTING DOUBLE TRIANGLE"},
            {L"♥", L"BLACK HEART SUIT"},
            {L"⬛", L"BLACK LARGE SQUARE"},
            {L"⏪", L"BLACK LEFT-POINTING DOUBLE TRIANGLE"},
            {L"◀", L"BLACK LEFT-POINTING TRIANGLE"},
            {L"◾", L"BLACK MEDIUM SMALL SQUARE"},
            {L"◼", L"BLACK MEDIUM SQUARE"},
            {L"✒", L"BLACK NIB"},
            {L"❓", L"BLACK QUESTION MARK ORNAMENT"},
            {L"⏩", L"BLACK RIGHT-POINTING DOUBLE TRIANGLE"},
            {L"▶", L"BLACK RIGHT-POINTING TRIANGLE"},
            {L"➡", L"BLACK RIGHTWARDS ARROW"},
            {L"✂", L"BLACK SCISSORS"},
            {L"▪", L"BLACK SMALL SQUARE"},
            {L"♠", L"BLACK SPADE SUIT"},
            {L"🔲", L"BLACK SQUARE BUTTON"},
            {L"☀", L"BLACK SUN WITH RAYS"},
            {L"☎", L"BLACK TELEPHONE"},
            {L"♻", L"BLACK UNIVERSAL RECYCLING SYMBOL"},
            {L"⏫", L"BLACK UP-POINTING DOUBLE TRIANGLE"},
            {L"🌼", L"BLOSSOM"},
            {L"🐡", L"BLOWFISH"},
            {L"📘", L"BLUE BOOK"},
            {L"💙", L"BLUE HEART"},
            {L"🐗", L"BOAR"},
            {L"💣", L"BOMB"},
            {L"🔖", L"BOOKMARK"},
            {L"📑", L"BOOKMARK TABS"},
            {L"📚", L"BOOKS"},
            {L"💐", L"BOUQUET"},
            {L"🎳", L"BOWLING"},
            {L"👦", L"BOY"},
            {L"🍞", L"BREAD"},
            {L"👰", L"BRIDE WITH VEIL"},
            {L"🌉", L"BRIDGE AT NIGHT"},
            {L"💼", L"BRIEFCASE"},
            {L"💔", L"BROKEN HEART"},
            {L"🐛", L"BUG"},
            {L"🚌", L"BUS"},
            {L"🚏", L"BUS STOP"},
            {L"👤", L"BUST IN SILHOUETTE"},
            {L"👥", L"BUSTS IN SILHOUETTE"},
            {L"🌵", L"CACTUS"},
            {L"📅", L"CALENDAR"},
            {L"📷", L"CAMERA"},
            {L"♋", L"CANCER"},
            {L"🍬", L"CANDY"},
            {L"♑", L"CAPRICORN"},
            {L"📇", L"CARD INDEX"},
            {L"🎠", L"CAROUSEL HORSE"},
            {L"🎏", L"CARP STREAMER"},
            {L"🐈", L"CAT"},
            {L"🐱", L"CAT FACE"},
            {L"😹", L"CAT FACE WITH TEARS OF JOY"},
            {L"😼", L"CAT FACE WITH WRY SMILE"},
            {L"📉", L"CHART WITH DOWNWARDS TREND"},
            {L"📈", L"CHART WITH UPWARDS TREND"},
            {L"💹", L"CHART WITH UPWARDS TREND AND YEN SIGN"},
            {L"📣", L"CHEERING MEGAPHONE"},
            {L"🏁", L"CHEQUERED FLAG"},
            {L"🍒", L"CHERRIES"},
            {L"🌸", L"CHERRY BLOSSOM"},
            {L"🌰", L"CHESTNUT"},
            {L"🐔", L"CHICKEN"},
            {L"🚸", L"CHILDREN CROSSING"},
            {L"🍫", L"CHOCOLATE BAR"},
            {L"🎄", L"CHRISTMAS TREE"},
            {L"⛪", L"CHURCH"},
            {L"🎦", L"CINEMA"},
            {L"🉑", L"CIRCLED IDEOGRAPH ACCEPT"},
            {L"🉐", L"CIRCLED IDEOGRAPH ADVANTAGE"},
            {L"㊗", L"CIRCLED IDEOGRAPH CONGRATULATION"},
            {L"㊙", L"CIRCLED IDEOGRAPH SECRET"},
            {L"Ⓜ", L"CIRCLED LATIN CAPITAL LETTER M"},
            {L"🎪", L"CIRCUS TENT"},
            {L"🌆", L"CITYSCAPE AT DUSK"},
            {L"🎬", L"CLAPPER BOARD"},
            {L"👏", L"CLAPPING HANDS SIGN"},
            {L"🍻", L"CLINKING BEER MUGS"},
            {L"📋", L"CLIPBOARD"},
            {L"🕗", L"CLOCK FACE EIGHT OCLOCK"},
            {L"🕣", L"CLOCK FACE EIGHT-THIRTY"},
            {L"🕚", L"CLOCK FACE ELEVEN OCLOCK"},
            {L"🕦", L"CLOCK FACE ELEVEN-THIRTY"},
            {L"🕔", L"CLOCK FACE FIVE OCLOCK"},
            {L"🕠", L"CLOCK FACE FIVE-THIRTY"},
            {L"🕓", L"CLOCK FACE FOUR OCLOCK"},
            {L"🕟", L"CLOCK FACE FOUR-THIRTY"},
            {L"🕘", L"CLOCK FACE NINE OCLOCK"},
            {L"🕤", L"CLOCK FACE NINE-THIRTY"},
            {L"🕐", L"CLOCK FACE ONE OCLOCK"},
            {L"🕜", L"CLOCK FACE ONE-THIRTY"},
            {L"🕖", L"CLOCK FACE SEVEN OCLOCK"},
            {L"🕢", L"CLOCK FACE SEVEN-THIRTY"},
            {L"🕕", L"CLOCK FACE SIX OCLOCK"},
            {L"🕡", L"CLOCK FACE SIX-THIRTY"},
            {L"🕙", L"CLOCK FACE TEN OCLOCK"},
            {L"🕥", L"CLOCK FACE TEN-THIRTY"},
            {L"🕒", L"CLOCK FACE THREE OCLOCK"},
            {L"🕞", L"CLOCK FACE THREE-THIRTY"},
            {L"🕛", L"CLOCK FACE TWELVE OCLOCK"},
            {L"🕧", L"CLOCK FACE TWELVE-THIRTY"},
            {L"🕑", L"CLOCK FACE TWO OCLOCK"},
            {L"🕝", L"CLOCK FACE TWO-THIRTY"},
            {L"🔃", L"CLOCKWISE DOWNWARDS AND UPWARDS OPEN CIRCLE ARROWS"},
            {L"🔁", L"CLOCKWISE RIGHTWARDS AND LEFTWARDS OPEN CIRCLE ARROWS"},
            {L"🔂", L"CLOCKWISE RIGHTWARDS AND LEFTWARDS OPEN CIRCLE ARROWS WITH CIRCLED ONE OVERLAY"},
            {L"📕", L"CLOSED BOOK"},
            {L"🔐", L"CLOSED LOCK WITH KEY"},
            {L"📪", L"CLOSED MAILBOX WITH LOWERED FLAG"},
            {L"📫", L"CLOSED MAILBOX WITH RAISED FLAG"},
            {L"🌂", L"CLOSED UMBRELLA"},
            {L"☁", L"CLOUD"},
            {L"🍸", L"COCKTAIL GLASS"},
            {L"💥", L"COLLISION SYMBOL"},
            {L"🎊", L"CONFETTI BALL"},
            {L"😖", L"CONFOUNDED FACE"},
            {L"😕", L"CONFUSED FACE"},
            {L"🚧", L"CONSTRUCTION SIGN"},
            {L"👷", L"CONSTRUCTION WORKER"},
            {L"🏪", L"CONVENIENCE STORE"},
            {L"🍚", L"COOKED RICE"},
            {L"🍪", L"COOKIE"},
            {L"🍳", L"COOKING"},
            {L"©", L"COPYRIGHT SIGN"},
            {L"💑", L"COUPLE WITH HEART"},
            {L"🐄", L"COW"},
            {L"🐮", L"COW FACE"},
            {L"💳", L"CREDIT CARD"},
            {L"🌙", L"CRESCENT MOON"},
            {L"🐊", L"CROCODILE"},
            {L"❌", L"CROSS MARK"},
            {L"🎌", L"CROSSED FLAGS"},
            {L"👑", L"CROWN"},
            {L"😿", L"CRYING CAT FACE"},
            {L"😢", L"CRYING FACE"},
            {L"🔮", L"CRYSTAL BALL"},
            {L"➰", L"CURLY LOOP"},
            {L"💱", L"CURRENCY EXCHANGE"},
            {L"🍛", L"CURRY AND RICE"},
            {L"🍮", L"CUSTARD"},
            {L"🛃", L"CUSTOMS"},
            {L"🌀", L"CYCLONE"},
            {L"💃", L"DANCER"},
            {L"🍡", L"DANGO"},
            {L"💨", L"DASH SYMBOL"},
            {L"🌳", L"DECIDUOUS TREE"},
            {L"🚚", L"DELIVERY TRUCK"},
            {L"🏬", L"DEPARTMENT STORE"},
            {L"💠", L"DIAMOND SHAPE WITH A DOT INSIDE"},
            {L"8⃣", L"DIGIT EIGHT + COMBINING ENCLOSING KEYCAP"},
            {L"5⃣", L"DIGIT FIVE + COMBINING ENCLOSING KEYCAP"},
            {L"4⃣", L"DIGIT FOUR + COMBINING ENCLOSING KEYCAP"},
            {L"9⃣", L"DIGIT NINE + COMBINING ENCLOSING KEYCAP"},
            {L"1⃣", L"DIGIT ONE + COMBINING ENCLOSING KEYCAP"},
            {L"7⃣", L"DIGIT SEVEN + COMBINING ENCLOSING KEYCAP"},
            {L"6⃣", L"DIGIT SIX + COMBINING ENCLOSING KEYCAP"},
            {L"3⃣", L"DIGIT THREE + COMBINING ENCLOSING KEYCAP"},
            {L"2⃣", L"DIGIT TWO + COMBINING ENCLOSING KEYCAP"},
            {L"0⃣", L"DIGIT ZERO + COMBINING ENCLOSING KEYCAP"},
            {L"🎯", L"DIRECT HIT"},
            {L"😥", L"DISAPPOINTED BUT RELIEVED FACE"},
            {L"😞", L"DISAPPOINTED FACE"},
            {L"😵", L"DIZZY FACE"},
            {L"💫", L"DIZZY SYMBOL"},
            {L"🚯", L"DO NOT LITTER SYMBOL"},
            {L"🐕", L"DOG"},
            {L"🐶", L"DOG FACE"},
            {L"🐬", L"DOLPHIN"},
            {L"🚪", L"DOOR"},
            {L"‼", L"DOUBLE EXCLAMATION MARK"},
            {L"🍩", L"DOUGHNUT"},
            {L"🔻", L"DOWN-POINTING RED TRIANGLE"},
            {L"🔽", L"DOWN-POINTING SMALL RED TRIANGLE"},
            {L"⬇", L"DOWNWARDS BLACK ARROW"},
            {L"🐉", L"DRAGON"},
            {L"🐲", L"DRAGON FACE"},
            {L"👗", L"DRESS"},
            {L"🐪", L"DROMEDARY CAMEL"},
            {L"💧", L"DROPLET"},
            {L"📀", L"DVD"},
            {L"📧", L"E-MAIL SYMBOL"},
            {L"👂", L"EAR"},
            {L"🌽", L"EAR OF MAIZE"},
            {L"🌾", L"EAR OF RICE"},
            {L"🌎", L"EARTH GLOBE AMERICAS"},
            {L"🌏", L"EARTH GLOBE ASIA-AUSTRALIA"},
            {L"🌍", L"EARTH GLOBE EUROPE-AFRICA"},
            {L"✴", L"EIGHT POINTED BLACK STAR"},
            {L"✳", L"EIGHT SPOKED ASTERISK"},
            {L"💡", L"ELECTRIC LIGHT BULB"},
            {L"🔌", L"ELECTRIC PLUG"},
            {L"🔦", L"ELECTRIC TORCH"},
            {L"🐘", L"ELEPHANT"},
            {L"🔚", L"END WITH LEFTWARDS ARROW ABOVE"},
            {L"✉", L"ENVELOPE"},
            {L"📩", L"ENVELOPE WITH DOWNWARDS ARROW ABOVE"},
            {L"🏰", L"EUROPEAN CASTLE"},
            {L"🏤", L"EUROPEAN POST OFFICE"},
            {L"🌲", L"EVERGREEN TREE"},
            {L"⁉", L"EXCLAMATION QUESTION MARK"},
            {L"😑", L"EXPRESSIONLESS FACE"},
            {L"👽", L"EXTRATERRESTRIAL ALIEN"},
            {L"👓", L"EYEGLASSES"},
            {L"👀", L"EYES"},
            {L"💆", L"FACE MASSAGE"},
            {L"😋", L"FACE SAVOURING DELICIOUS FOOD"},
            {L"😱", L"FACE SCREAMING IN FEAR"},
            {L"😘", L"FACE THROWING A KISS"},
            {L"😓", L"FACE WITH COLD SWEAT"},
            {L"😤", L"FACE WITH LOOK OF TRIUMPH"},
            {L"😷", L"FACE WITH MEDICAL MASK"},
            {L"🙅", L"FACE WITH NO GOOD GESTURE"},
            {L"🙆", L"FACE WITH OK GESTURE"},
            {L"😮", L"FACE WITH OPEN MOUTH"},
            {L"😰", L"FACE WITH OPEN MOUTH AND COLD SWEAT"},
            {L"😛", L"FACE WITH STUCK-OUT TONGUE"},
            {L"😝", L"FACE WITH STUCK-OUT TONGUE AND TIGHTLY-CLOSED EYES"},
            {L"😜", L"FACE WITH STUCK-OUT TONGUE AND WINKING EYE"},
            {L"😂", L"FACE WITH TEARS OF JOY"},
            {L"😶", L"FACE WITHOUT MOUTH"},
            {L"🏭", L"FACTORY"},
            {L"🍂", L"FALLEN LEAF"},
            {L"👪", L"FAMILY"},
            {L"🎅", L"FATHER CHRISTMAS"},
            {L"📠", L"FAX MACHINE"},
            {L"😨", L"FEARFUL FACE"},
            {L"🎡", L"FERRIS WHEEL"},
            {L"📁", L"FILE FOLDER"},
            {L"🔥", L"FIRE"},
            {L"🚒", L"FIRE ENGINE"},
            {L"🎇", L"FIREWORK SPARKLER"},
            {L"🎆", L"FIREWORKS"},
            {L"🌓", L"FIRST QUARTER MOON SYMBOL"},
            {L"🌛", L"FIRST QUARTER MOON WITH FACE"},
            {L"🐟", L"FISH"},
            {L"🍥", L"FISH CAKE WITH SWIRL DESIGN"},
            {L"🎣", L"FISHING POLE AND FISH"},
            {L"👊", L"FISTED HAND SIGN"},
            {L"⛳", L"FLAG IN HOLE"},
            {L"💪", L"FLEXED BICEPS"},
            {L"💾", L"FLOPPY DISK"},
            {L"🎴", L"FLOWER PLAYING CARDS"},
            {L"😳", L"FLUSHED FACE"},
            {L"🌁", L"FOGGY"},
            {L"👣", L"FOOTPRINTS"},
            {L"🍴", L"FORK AND KNIFE"},
            {L"⛲", L"FOUNTAIN"},
            {L"🍀", L"FOUR LEAF CLOVER"},
            {L"🍟", L"FRENCH FRIES"},
            {L"🍤", L"FRIED SHRIMP"},
            {L"🐸", L"FROG FACE"},
            {L"🐥", L"FRONT-FACING BABY CHICK"},
            {L"😦", L"FROWNING FACE WITH OPEN MOUTH"},
            {L"⛽", L"FUEL PUMP"},
            {L"🌕", L"FULL MOON SYMBOL"},
            {L"🌝", L"FULL MOON WITH FACE"},
            {L"🎲", L"GAME DIE"},
            {L"💎", L"GEM STONE"},
            {L"♊", L"GEMINI"},
            {L"👻", L"GHOST"},
            {L"👧", L"GIRL"},
            {L"🌐", L"GLOBE WITH MERIDIANS"},
            {L"🌟", L"GLOWING STAR"},
            {L"🐐", L"GOAT"},
            {L"🎓", L"GRADUATION CAP"},
            {L"🍇", L"GRAPES"},
            {L"🍏", L"GREEN APPLE"},
            {L"📗", L"GREEN BOOK"},
            {L"💚", L"GREEN HEART"},
            {L"😬", L"GRIMACING FACE"},
            {L"😸", L"GRINNING CAT FACE WITH SMILING EYES"},
            {L"😀", L"GRINNING FACE"},
            {L"😁", L"GRINNING FACE WITH SMILING EYES"},
            {L"💗", L"GROWING HEART"},
            {L"💂", L"GUARDSMAN"},
            {L"🎸", L"GUITAR"},
            {L"💇", L"HAIRCUT"},
            {L"🍔", L"HAMBURGER"},
            {L"🔨", L"HAMMER"},
            {L"🐹", L"HAMSTER FACE"},
            {L"👜", L"HANDBAG"},
            {L"🙋", L"HAPPY PERSON RAISING ONE HAND"},
            {L"🐣", L"HATCHING CHICK"},
            {L"🎧", L"HEADPHONE"},
            {L"🙉", L"HEAR-NO-EVIL MONKEY"},
            {L"💟", L"HEART DECORATION"},
            {L"💘", L"HEART WITH ARROW"},
            {L"💝", L"HEART WITH RIBBON"},
            {L"❤", L"HEAVY BLACK HEART"},
            {L"✔", L"HEAVY CHECK MARK"},
            {L"➗", L"HEAVY DIVISION SIGN"},
            {L"💲", L"HEAVY DOLLAR SIGN"},
            {L"❗", L"HEAVY EXCLAMATION MARK SYMBOL"},
            {L"⭕", L"HEAVY LARGE CIRCLE"},
            {L"➖", L"HEAVY MINUS SIGN"},
            {L"✖", L"HEAVY MULTIPLICATION X"},
            {L"➕", L"HEAVY PLUS SIGN"},
            {L"🚁", L"HELICOPTER"},
            {L"🌿", L"HERB"},
            {L"🌺", L"HIBISCUS"},
            {L"🔆", L"HIGH BRIGHTNESS SYMBOL"},
            {L"⚡", L"HIGH VOLTAGE SIGN"},
            {L"👠", L"HIGH-HEELED SHOE"},
            {L"🚄", L"HIGH-SPEED TRAIN"},
            {L"🚅", L"HIGH-SPEED TRAIN WITH BULLET NOSE"},
            {L"🔪", L"HOCHO"},
            {L"🍯", L"HONEY POT"},
            {L"🐝", L"HONEYBEE"},
            {L"🚥", L"HORIZONTAL TRAFFIC LIGHT"},
            {L"🐎", L"HORSE"},
            {L"🐴", L"HORSE FACE"},
            {L"🏇", L"HORSE RACING"},
            {L"🏥", L"HOSPITAL"},
            {L"☕", L"HOT BEVERAGE"},
            {L"♨", L"HOT SPRINGS"},
            {L"🏨", L"HOTEL"},
            {L"⌛", L"HOURGLASS"},
            {L"⏳", L"HOURGLASS WITH FLOWING SAND"},
            {L"🏠", L"HOUSE BUILDING"},
            {L"🏡", L"HOUSE WITH GARDEN"},
            {L"💯", L"HUNDRED POINTS SYMBOL"},
            {L"😯", L"HUSHED FACE"},
            {L"🍨", L"ICE CREAM"},
            {L"👿", L"IMP"},
            {L"📥", L"INBOX TRAY"},
            {L"📨", L"INCOMING ENVELOPE"},
            {L"💁", L"INFORMATION DESK PERSON"},
            {L"ℹ", L"INFORMATION SOURCE"},
            {L"🔠", L"INPUT SYMBOL FOR LATIN CAPITAL LETTERS"},
            {L"🔤", L"INPUT SYMBOL FOR LATIN LETTERS"},
            {L"🔡", L"INPUT SYMBOL FOR LATIN SMALL LETTERS"},
            {L"🔢", L"INPUT SYMBOL FOR NUMBERS"},
            {L"🔣", L"INPUT SYMBOL FOR SYMBOLS"},
            {L"🏮", L"IZAKAYA LANTERN"},
            {L"🎃", L"JACK-O-LANTERN"},
            {L"🏯", L"JAPANESE CASTLE"},
            {L"🎎", L"JAPANESE DOLLS"},
            {L"👺", L"JAPANESE GOBLIN"},
            {L"👹", L"JAPANESE OGRE"},
            {L"🏣", L"JAPANESE POST OFFICE"},
            {L"🔰", L"JAPANESE SYMBOL FOR BEGINNER"},
            {L"👖", L"JEANS"},
            {L"🔑", L"KEY"},
            {L"🔟", L"KEYCAP TEN"},
            {L"👘", L"KIMONO"},
            {L"💏", L"KISS"},
            {L"💋", L"KISS MARK"},
            {L"😽", L"KISSING CAT FACE WITH CLOSED EYES"},
            {L"😗", L"KISSING FACE"},
            {L"😚", L"KISSING FACE WITH CLOSED EYES"},
            {L"😙", L"KISSING FACE WITH SMILING EYES"},
            {L"🐨", L"KOALA"},
            {L"🐞", L"LADY BEETLE"},
            {L"🔵", L"LARGE BLUE CIRCLE"},
            {L"🔷", L"LARGE BLUE DIAMOND"},
            {L"🔶", L"LARGE ORANGE DIAMOND"},
            {L"🔴", L"LARGE RED CIRCLE"},
            {L"🌗", L"LAST QUARTER MOON SYMBOL"},
            {L"🌜", L"LAST QUARTER MOON WITH FACE"},
            {L"🍃", L"LEAF FLUTTERING IN WIND"},
            {L"📒", L"LEDGER"},
            {L"🛅", L"LEFT LUGGAGE"},
            {L"↔", L"LEFT RIGHT ARROW"},
            {L"🔍", L"LEFT-POINTING MAGNIFYING GLASS"},
            {L"↩", L"LEFTWARDS ARROW WITH HOOK"},
            {L"⬅", L"LEFTWARDS BLACK ARROW"},
            {L"🍋", L"LEMON"},
            {L"♌", L"LEO"},
            {L"🐆", L"LEOPARD"},
            {L"♎", L"LIBRA"},
            {L"🚈", L"LIGHT RAIL"},
            {L"🔗", L"LINK SYMBOL"},
            {L"💄", L"LIPSTICK"},
            {L"🔒", L"LOCK"},
            {L"🔏", L"LOCK WITH INK PEN"},
            {L"🍭", L"LOLLIPOP"},
            {L"😭", L"LOUDLY CRYING FACE"},
            {L"🏩", L"LOVE HOTEL"},
            {L"💌", L"LOVE LETTER"},
            {L"🔅", L"LOW BRIGHTNESS SYMBOL"},
            {L"🀄", L"MAHJONG TILE RED DRAGON"},
            {L"👨", L"MAN"},
            {L"👫", L"MAN AND WOMAN HOLDING HANDS"},
            {L"👲", L"MAN WITH GUA PI MAO"},
            {L"👳", L"MAN WITH TURBAN"},
            {L"👞", L"MANS SHOE"},
            {L"🍁", L"MAPLE LEAF"},
            {L"🍖", L"MEAT ON BONE"},
            {L"⚫", L"MEDIUM BLACK CIRCLE"},
            {L"⚪", L"MEDIUM WHITE CIRCLE"},
            {L"🍈", L"MELON"},
            {L"📝", L"MEMO"},
            {L"🚹", L"MENS SYMBOL"},
            {L"🚇", L"METRO"},
            {L"🎤", L"MICROPHONE"},
            {L"🔬", L"MICROSCOPE"},
            {L"🌌", L"MILKY WAY"},
            {L"🚐", L"MINIBUS"},
            {L"💽", L"MINIDISC"},
            {L"📱", L"MOBILE PHONE"},
            {L"📴", L"MOBILE PHONE OFF"},
            {L"📲", L"MOBILE PHONE WITH RIGHTWARDS ARROW AT LEFT"},
            {L"💰", L"MONEY BAG"},
            {L"💸", L"MONEY WITH WINGS"},
            {L"🐒", L"MONKEY"},
            {L"🐵", L"MONKEY FACE"},
            {L"🚝", L"MONORAIL"},
            {L"🎑", L"MOON VIEWING CEREMONY"},
            {L"🗻", L"MOUNT FUJI"},
            {L"🚵", L"MOUNTAIN BICYCLIST"},
            {L"🚠", L"MOUNTAIN CABLEWAY"},
            {L"🚞", L"MOUNTAIN RAILWAY"},
            {L"🐁", L"MOUSE"},
            {L"🐭", L"MOUSE FACE"},
            {L"👄", L"MOUTH"},
            {L"🎥", L"MOVIE CAMERA"},
            {L"🗿", L"MOYAI"},
            {L"🎶", L"MULTIPLE MUSICAL NOTES"},
            {L"🍄", L"MUSHROOM"},
            {L"🎹", L"MUSICAL KEYBOARD"},
            {L"🎵", L"MUSICAL NOTE"},
            {L"🎼", L"MUSICAL SCORE"},
            {L"💅", L"NAIL POLISH"},
            {L"📛", L"NAME BADGE"},
            {L"👔", L"NECKTIE"},
            {L"🆎", L"NEGATIVE SQUARED AB"},
            {L"❎", L"NEGATIVE SQUARED CROSS MARK"},
            {L"🅰", L"NEGATIVE SQUARED LATIN CAPITAL LETTER A"},
            {L"🅱", L"NEGATIVE SQUARED LATIN CAPITAL LETTER B"},
            {L"🅾", L"NEGATIVE SQUARED LATIN CAPITAL LETTER O"},
            {L"🅿", L"NEGATIVE SQUARED LATIN CAPITAL LETTER P"},
            {L"😐", L"NEUTRAL FACE"},
            {L"🌑", L"NEW MOON SYMBOL"},
            {L"🌚", L"NEW MOON WITH FACE"},
            {L"📰", L"NEWSPAPER"},
            {L"🌃", L"NIGHT WITH STARS"},
            {L"🚳", L"NO BICYCLES"},
            {L"⛔", L"NO ENTRY"},
            {L"🚫", L"NO ENTRY SIGN"},
            {L"📵", L"NO MOBILE PHONES"},
            {L"🔞", L"NO ONE UNDER EIGHTEEN SYMBOL"},
            {L"🚷", L"NO PEDESTRIANS"},
            {L"🚭", L"NO SMOKING SYMBOL"},
            {L"🚱", L"NON-POTABLE WATER SYMBOL"},
            {L"↗", L"NORTH EAST ARROW"},
            {L"↖", L"NORTH WEST ARROW"},
            {L"👃", L"NOSE"},
            {L"📓", L"NOTEBOOK"},
            {L"📔", L"NOTEBOOK WITH DECORATIVE COVER"},
            {L"#⃣", L"NUMBER SIGN + COMBINING ENCLOSING KEYCAP"},
            {L"🔩", L"NUT AND BOLT"},
            {L"🐙", L"OCTOPUS"},
            {L"🍢", L"ODEN"},
            {L"🏢", L"OFFICE BUILDING"},
            {L"👌", L"OK HAND SIGN"},
            {L"👴", L"OLDER MAN"},
            {L"👵", L"OLDER WOMAN"},
            {L"🔛", L"ON WITH EXCLAMATION MARK WITH LEFT RIGHT ARROW ABOVE"},
            {L"🚘", L"ONCOMING AUTOMOBILE"},
            {L"🚍", L"ONCOMING BUS"},
            {L"🚔", L"ONCOMING POLICE CAR"},
            {L"🚖", L"ONCOMING TAXI"},
            {L"📖", L"OPEN BOOK"},
            {L"📂", L"OPEN FILE FOLDER"},
            {L"👐", L"OPEN HANDS SIGN"},
            {L"🔓", L"OPEN LOCK"},
            {L"📭", L"OPEN MAILBOX WITH LOWERED FLAG"},
            {L"📬", L"OPEN MAILBOX WITH RAISED FLAG"},
            {L"⛎", L"OPHIUCHUS"},
            {L"💿", L"OPTICAL DISC"},
            {L"📙", L"ORANGE BOOK"},
            {L"📤", L"OUTBOX TRAY"},
            {L"🐂", L"OX"},
            {L"📦", L"PACKAGE"},
            {L"📄", L"PAGE FACING UP"},
            {L"📃", L"PAGE WITH CURL"},
            {L"📟", L"PAGER"},
            {L"🌴", L"PALM TREE"},
            {L"🐼", L"PANDA FACE"},
            {L"📎", L"PAPERCLIP"},
            {L"〽", L"PART ALTERNATION MARK"},
            {L"🎉", L"PARTY POPPER"},
            {L"🛂", L"PASSPORT CONTROL"},
            {L"🐾", L"PAW PRINTS"},
            {L"🍑", L"PEACH"},
            {L"🍐", L"PEAR"},
            {L"🚶", L"PEDESTRIAN"},
            {L"✏", L"PENCIL"},
            {L"🐧", L"PENGUIN"},
            {L"😔", L"PENSIVE FACE"},
            {L"🎭", L"PERFORMING ARTS"},
            {L"😣", L"PERSEVERING FACE"},
            {L"🙇", L"PERSON BOWING DEEPLY"},
            {L"🙍", L"PERSON FROWNING"},
            {L"🙌", L"PERSON RAISING BOTH HANDS IN CELEBRATION"},
            {L"👱", L"PERSON WITH BLOND HAIR"},
            {L"🙏", L"PERSON WITH FOLDED HANDS"},
            {L"🙎", L"PERSON WITH POUTING FACE"},
            {L"💻", L"PERSONAL COMPUTER"},
            {L"🐖", L"PIG"},
            {L"🐷", L"PIG FACE"},
            {L"🐽", L"PIG NOSE"},
            {L"💩", L"PILE OF POO"},
            {L"💊", L"PILL"},
            {L"🎍", L"PINE DECORATION"},
            {L"🍍", L"PINEAPPLE"},
            {L"♓", L"PISCES"},
            {L"🔫", L"PISTOL"},
            {L"🃏", L"PLAYING CARD BLACK JOKER"},
            {L"🚓", L"POLICE CAR"},
            {L"🚨", L"POLICE CARS REVOLVING LIGHT"},
            {L"👮", L"POLICE OFFICER"},
            {L"🐩", L"POODLE"},
            {L"📯", L"POSTAL HORN"},
            {L"📮", L"POSTBOX"},
            {L"🍲", L"POT OF FOOD"},
            {L"🚰", L"POTABLE WATER SYMBOL"},
            {L"👝", L"POUCH"},
            {L"🍗", L"POULTRY LEG"},
            {L"😾", L"POUTING CAT FACE"},
            {L"😡", L"POUTING FACE"},
            {L"👸", L"PRINCESS"},
            {L"📢", L"PUBLIC ADDRESS LOUDSPEAKER"},
            {L"💜", L"PURPLE HEART"},
            {L"👛", L"PURSE"},
            {L"📌", L"PUSHPIN"},
            {L"🚮", L"PUT LITTER IN ITS PLACE SYMBOL"},
            {L"🐇", L"RABBIT"},
            {L"🐰", L"RABBIT FACE"},
            {L"📻", L"RADIO"},
            {L"🔘", L"RADIO BUTTON"},
            {L"🚃", L"RAILWAY CAR"},
            {L"🌈", L"RAINBOW"},
            {L"✊", L"RAISED FIST"},
            {L"✋", L"RAISED HAND"},
            {L"🐏", L"RAM"},
            {L"🐀", L"RAT"},
            {L"🚙", L"RECREATIONAL VEHICLE"},
            {L"🍎", L"RED APPLE"},
            {L"🇨🇳", L"REGIONAL INDICATOR SYMBOL LETTER C + REGIONAL INDICATOR SYMBOL LETTER N"},
            {L"🇩🇪", L"REGIONAL INDICATOR SYMBOL LETTER D + REGIONAL INDICATOR SYMBOL LETTER E"},
            {L"🇪🇸", L"REGIONAL INDICATOR SYMBOL LETTER E + REGIONAL INDICATOR SYMBOL LETTER S"},
            {L"🇫🇷", L"REGIONAL INDICATOR SYMBOL LETTER F + REGIONAL INDICATOR SYMBOL LETTER R"},
            {L"🇬🇧", L"REGIONAL INDICATOR SYMBOL LETTER G + REGIONAL INDICATOR SYMBOL LETTER B"},
            {L"🇮🇹", L"REGIONAL INDICATOR SYMBOL LETTER I + REGIONAL INDICATOR SYMBOL LETTER T"},
            {L"🇯🇵", L"REGIONAL INDICATOR SYMBOL LETTER J + REGIONAL INDICATOR SYMBOL LETTER P"},
            {L"🇰🇷", L"REGIONAL INDICATOR SYMBOL LETTER K + REGIONAL INDICATOR SYMBOL LETTER R"},
            {L"🇷🇺", L"REGIONAL INDICATOR SYMBOL LETTER R + REGIONAL INDICATOR SYMBOL LETTER U"},
            {L"🇺🇸", L"REGIONAL INDICATOR SYMBOL LETTER U + REGIONAL INDICATOR SYMBOL LETTER S"},
            {L"®", L"REGISTERED SIGN"},
            {L"😌", L"RELIEVED FACE"},
            {L"🚻", L"RESTROOM"},
            {L"💞", L"REVOLVING HEARTS"},
            {L"🎀", L"RIBBON"},
            {L"🍙", L"RICE BALL"},
            {L"🍘", L"RICE CRACKER"},
            {L"🔎", L"RIGHT-POINTING MAGNIFYING GLASS"},
            {L"↪", L"RIGHTWARDS ARROW WITH HOOK"},
            {L"💍", L"RING"},
            {L"🍠", L"ROASTED SWEET POTATO"},
            {L"🚀", L"ROCKET"},
            {L"🎢", L"ROLLER COASTER"},
            {L"🐓", L"ROOSTER"},
            {L"🌹", L"ROSE"},
            {L"📍", L"ROUND PUSHPIN"},
            {L"🚣", L"ROWBOAT"},
            {L"🏉", L"RUGBY FOOTBALL"},
            {L"🏃", L"RUNNER"},
            {L"🎽", L"RUNNING SHIRT WITH SASH"},
            {L"♐", L"SAGITTARIUS"},
            {L"⛵", L"SAILBOAT"},
            {L"🍶", L"SAKE BOTTLE AND CUP"},
            {L"📡", L"SATELLITE ANTENNA"},
            {L"🎷", L"SAXOPHONE"},
            {L"🏫", L"SCHOOL"},
            {L"🎒", L"SCHOOL SATCHEL"},
            {L"♏", L"SCORPIUS"},
            {L"📜", L"SCROLL"},
            {L"💺", L"SEAT"},
            {L"🙈", L"SEE-NO-EVIL MONKEY"},
            {L"🌱", L"SEEDLING"},
            {L"🍧", L"SHAVED ICE"},
            {L"🐑", L"SHEEP"},
            {L"🚢", L"SHIP"},
            {L"🌠", L"SHOOTING STAR"},
            {L"🍰", L"SHORTCAKE"},
            {L"🚿", L"SHOWER"},
            {L"🗾", L"SILHOUETTE OF JAPAN"},
            {L"🔯", L"SIX POINTED STAR WITH MIDDLE DOT"},
            {L"🎿", L"SKI AND SKI BOOT"},
            {L"💀", L"SKULL"},
            {L"😴", L"SLEEPING FACE"},
            {L"💤", L"SLEEPING SYMBOL"},
            {L"😪", L"SLEEPY FACE"},
            {L"🍕", L"SLICE OF PIZZA"},
            {L"🎰", L"SLOT MACHINE"},
            {L"🔹", L"SMALL BLUE DIAMOND"},
            {L"🔸", L"SMALL ORANGE DIAMOND"},
            {L"😻", L"SMILING CAT FACE WITH HEART-SHAPED EYES"},
            {L"😺", L"SMILING CAT FACE WITH OPEN MOUTH"},
            {L"😇", L"SMILING FACE WITH HALO"},
            {L"😍", L"SMILING FACE WITH HEART-SHAPED EYES"},
            {L"😈", L"SMILING FACE WITH HORNS"},
            {L"😃", L"SMILING FACE WITH OPEN MOUTH"},
            {L"😅", L"SMILING FACE WITH OPEN MOUTH AND COLD SWEAT"},
            {L"😄", L"SMILING FACE WITH OPEN MOUTH AND SMILING EYES"},
            {L"😆", L"SMILING FACE WITH OPEN MOUTH AND TIGHTLY-CLOSED EYES"},
            {L"😊", L"SMILING FACE WITH SMILING EYES"},
            {L"😎", L"SMILING FACE WITH SUNGLASSES"},
            {L"😏", L"SMIRKING FACE"},
            {L"🚬", L"SMOKING SYMBOL"},
            {L"🐌", L"SNAIL"},
            {L"🐍", L"SNAKE"},
            {L"🏂", L"SNOWBOARDER"},
            {L"❄", L"SNOWFLAKE"},
            {L"⛄", L"SNOWMAN WITHOUT SNOW"},
            {L"⚽", L"SOCCER BALL"},
            {L"🍦", L"SOFT ICE CREAM"},
            {L"🔜", L"SOON WITH RIGHTWARDS ARROW ABOVE"},
            {L"↘", L"SOUTH EAST ARROW"},
            {L"↙", L"SOUTH WEST ARROW"},
            {L"🍝", L"SPAGHETTI"},
            {L"❇", L"SPARKLE"},
            {L"✨", L"SPARKLES"},
            {L"💖", L"SPARKLING HEART"},
            {L"🙊", L"SPEAK-NO-EVIL MONKEY"},
            {L"🔇", L"SPEAKER WITH CANCELLATION STROKE"},
            {L"🔉", L"SPEAKER WITH ONE SOUND WAVE"},
            {L"🔊", L"SPEAKER WITH THREE SOUND WAVES"},
            {L"💬", L"SPEECH BALLOON"},
            {L"🚤", L"SPEEDBOAT"},
            {L"🐚", L"SPIRAL SHELL"},
            {L"💦", L"SPLASHING SWEAT SYMBOL"},
            {L"🐳", L"SPOUTING WHALE"},
            {L"🈹", L"SQUARED CJK UNIFIED IDEOGRAPH-5272"},
            {L"🈴", L"SQUARED CJK UNIFIED IDEOGRAPH-5408"},
            {L"🈺", L"SQUARED CJK UNIFIED IDEOGRAPH-55B6"},
            {L"🈯", L"SQUARED CJK UNIFIED IDEOGRAPH-6307"},
            {L"🈷", L"SQUARED CJK UNIFIED IDEOGRAPH-6708"},
            {L"🈶", L"SQUARED CJK UNIFIED IDEOGRAPH-6709"},
            {L"🈵", L"SQUARED CJK UNIFIED IDEOGRAPH-6E80"},
            {L"🈚", L"SQUARED CJK UNIFIED IDEOGRAPH-7121"},
            {L"🈸", L"SQUARED CJK UNIFIED IDEOGRAPH-7533"},
            {L"🈲", L"SQUARED CJK UNIFIED IDEOGRAPH-7981"},
            {L"🈳", L"SQUARED CJK UNIFIED IDEOGRAPH-7A7A"},
            {L"🆑", L"SQUARED CL"},
            {L"🆒", L"SQUARED COOL"},
            {L"🆓", L"SQUARED FREE"},
            {L"🆔", L"SQUARED ID"},
            {L"🈁", L"SQUARED KATAKANA KOKO"},
            {L"🈂", L"SQUARED KATAKANA SA"},
            {L"🆕", L"SQUARED NEW"},
            {L"🆖", L"SQUARED NG"},
            {L"🆗", L"SQUARED OK"},
            {L"🆘", L"SQUARED SOS"},
            {L"🆙", L"SQUARED UP WITH EXCLAMATION MARK"},
            {L"🆚", L"SQUARED VS"},
            {L"🚉", L"STATION"},
            {L"🗽", L"STATUE OF LIBERTY"},
            {L"🚂", L"STEAM LOCOMOTIVE"},
            {L"🍜", L"STEAMING BOWL"},
            {L"📏", L"STRAIGHT RULER"},
            {L"🍓", L"STRAWBERRY"},
            {L"⛅", L"SUN BEHIND CLOUD"},
            {L"🌞", L"SUN WITH FACE"},
            {L"🌻", L"SUNFLOWER"},
            {L"🌅", L"SUNRISE"},
            {L"🌄", L"SUNRISE OVER MOUNTAINS"},
            {L"🌇", L"SUNSET OVER BUILDINGS"},
            {L"🏄", L"SURFER"},
            {L"🍣", L"SUSHI"},
            {L"🚟", L"SUSPENSION RAILWAY"},
            {L"🏊", L"SWIMMER"},
            {L"💉", L"SYRINGE"},
            {L"👕", L"T-SHIRT"},
            {L"🎋", L"TANABATA TREE"},
            {L"🍊", L"TANGERINE"},
            {L"♉", L"TAURUS"},
            {L"🚕", L"TAXI"},
            {L"🍵", L"TEACUP WITHOUT HANDLE"},
            {L"📆", L"TEAR-OFF CALENDAR"},
            {L"📞", L"TELEPHONE RECEIVER"},
            {L"🔭", L"TELESCOPE"},
            {L"📺", L"TELEVISION"},
            {L"🎾", L"TENNIS RACQUET AND BALL"},
            {L"⛺", L"TENT"},
            {L"💭", L"THOUGHT BALLOON"},
            {L"👎", L"THUMBS DOWN SIGN"},
            {L"👍", L"THUMBS UP SIGN"},
            {L"🎫", L"TICKET"},
            {L"🐅", L"TIGER"},
            {L"🐯", L"TIGER FACE"},
            {L"😫", L"TIRED FACE"},
            {L"🚽", L"TOILET"},
            {L"🗼", L"TOKYO TOWER"},
            {L"🍅", L"TOMATO"},
            {L"👅", L"TONGUE"},
            {L"🎩", L"TOP HAT"},
            {L"🔝", L"TOP WITH UPWARDS ARROW ABOVE"},
            {L"🚜", L"TRACTOR"},
            {L"™", L"TRADE MARK SIGN"},
            {L"🚆", L"TRAIN"},
            {L"🚊", L"TRAM"},
            {L"🚩", L"TRIANGULAR FLAG ON POST"},
            {L"📐", L"TRIANGULAR RULER"},
            {L"🔱", L"TRIDENT EMBLEM"},
            {L"🚎", L"TROLLEYBUS"},
            {L"🏆", L"TROPHY"},
            {L"🍹", L"TROPICAL DRINK"},
            {L"🐠", L"TROPICAL FISH"},
            {L"🎺", L"TRUMPET"},
            {L"🌷", L"TULIP"},
            {L"🐢", L"TURTLE"},
            {L"🔀", L"TWISTED RIGHTWARDS ARROWS"},
            {L"💕", L"TWO HEARTS"},
            {L"👬", L"TWO MEN HOLDING HANDS"},
            {L"👭", L"TWO WOMEN HOLDING HANDS"},
            {L"☔", L"UMBRELLA WITH RAIN DROPS"},
            {L"😒", L"UNAMUSED FACE"},
            {L"↕", L"UP DOWN ARROW"},
            {L"🔺", L"UP-POINTING RED TRIANGLE"},
            {L"🔼", L"UP-POINTING SMALL RED TRIANGLE"},
            {L"⬆", L"UPWARDS BLACK ARROW"},
            {L"🚦", L"VERTICAL TRAFFIC LIGHT"},
            {L"📳", L"VIBRATION MODE"},
            {L"✌", L"VICTORY HAND"},
            {L"📹", L"VIDEO CAMERA"},
            {L"🎮", L"VIDEO GAME"},
            {L"📼", L"VIDEOCASSETTE"},
            {L"🎻", L"VIOLIN"},
            {L"♍", L"VIRGO"},
            {L"🌋", L"VOLCANO"},
            {L"🌘", L"WANING CRESCENT MOON SYMBOL"},
            {L"🌖", L"WANING GIBBOUS MOON SYMBOL"},
            {L"⚠", L"WARNING SIGN"},
            {L"⌚", L"WATCH"},
            {L"🐃", L"WATER BUFFALO"},
            {L"🚾", L"WATER CLOSET"},
            {L"🌊", L"WATER WAVE"},
            {L"🍉", L"WATERMELON"},
            {L"👋", L"WAVING HAND SIGN"},
            {L"〰", L"WAVY DASH"},
            {L"🌒", L"WAXING CRESCENT MOON SYMBOL"},
            {L"🌔", L"WAXING GIBBOUS MOON SYMBOL"},
            {L"🙀", L"WEARY CAT FACE"},
            {L"😩", L"WEARY FACE"},
            {L"💒", L"WEDDING"},
            {L"🐋", L"WHALE"},
            {L"♿", L"WHEELCHAIR SYMBOL"},
            {L"👇", L"WHITE DOWN POINTING BACKHAND INDEX"},
            {L"❕", L"WHITE EXCLAMATION MARK ORNAMENT"},
            {L"💮", L"WHITE FLOWER"},
            {L"✅", L"WHITE HEAVY CHECK MARK"},
            {L"⬜", L"WHITE LARGE SQUARE"},
            {L"👈", L"WHITE LEFT POINTING BACKHAND INDEX"},
            {L"◽", L"WHITE MEDIUM SMALL SQUARE"},
            {L"◻", L"WHITE MEDIUM SQUARE"},
            {L"⭐", L"WHITE MEDIUM STAR"},
            {L"❔", L"WHITE QUESTION MARK ORNAMENT"},
            {L"👉", L"WHITE RIGHT POINTING BACKHAND INDEX"},
            {L"▫", L"WHITE SMALL SQUARE"},
            {L"☺", L"WHITE SMILING FACE"},
            {L"🔳", L"WHITE SQUARE BUTTON"},
            {L"👆", L"WHITE UP POINTING BACKHAND INDEX"},
            {L"☝", L"WHITE UP POINTING INDEX"},
            {L"🎐", L"WIND CHIME"},
            {L"🍷", L"WINE GLASS"},
            {L"😉", L"WINKING FACE"},
            {L"🐺", L"WOLF FACE"},
            {L"👩", L"WOMAN"},
            {L"👯", L"WOMAN WITH BUNNY EARS"},
            {L"👢", L"WOMANS BOOTS"},
            {L"👚", L"WOMANS CLOTHES"},
            {L"👒", L"WOMANS HAT"},
            {L"👡", L"WOMANS SANDAL"},
            {L"🚺", L"WOMENS SYMBOL"},
            {L"😟", L"WORRIED FACE"},
            {L"🎁", L"WRAPPED PRESENT"},
            {L"🔧", L"WRENCH"},
            {L"💛", L"YELLOW HEART"}
    };

    wstring get_text(wstring target) {
        if (emojis.find(target) == emojis.end()) {
            return target;
        }
        wstring value = emojis[target];
        transform(value.begin(), value.end(), value.begin(), ::tolower);
        return value;
    }
}

