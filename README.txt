Βασιλάκης Βασίλης (sdi1800018) και Παναγοπούλου Αγγελική (sdi1800141) - Ομαδική Εργασία OOP

Αρχεία
    • Card.hpp
        Κλάσεις Card, GreenCard, BlackCard

    • Follower.hpp
        Κλάση Follower και τα είδη της: Footsoldier, Archer, Cavalry, Bushido, Sieger, Atakebune

    • Item.hpp
        Κλάση Item και τα είδη της: Katana, Spear, Bow, Ninjato, Wakizashi

    • Holding.hpp
        Κλάση Holding και τα είδη της: Plain, Mine, GoldMine, CrystalMine, Farmland, GiftsandFavour, Stronghold

    • Personality.hpp/Personality.cpp
        Κλάση Personality και τα είδη της: Attacker, Defender, Champion, Chancellor, Shogun
        Στο Personality.cpp περιέχονται οι συναρτήσεις της κλάσης Personality

    • Player.hpp/Player.cpp
        Κλάση Player

    • GameBoard.hpp/GameBoard.cpp
        Κλάση GameBoard

    • DeckBuilder.hpp/DeckBuilder.cpp και TypeConverter.hpp/TypeConverter.cpp
        Τα βοητικά αρχεία της εργασίας που δόθηκαν

    • CardTextes.txt
        Ιαπωνικές φράσεις που εισάγονται στο πεδίο cardText των GreenCard

    • main.cpp
        Η συνάρτηση main

    • Makefile

Μεταγλώττιση
    • g++ -o ex main.cpp DeckBuilder.cpp Personality.cpp Player.cpp GameBoard.cpp TypeConverter.cpp

Εκτέλεση
    • ./ex

Αναπαραστάσεις δεδομένων- Παραδοχές- Αιτιολογήσεις σχεδιαστικών επιλογών
    1. Card.hpp
        • Η κλάση Card είναι abstract και οι κλάσεις GreenCard, BlackCard είναι υποκλάσεις αυτής.
        • Στην κλάση Card τα μέλη-δεδομένα cost και isTapped είναι protected για να μπορούν να αρχικοποιηθούν ή να τροποποιηθούν στις υποκλάσεις της. Ομοίως για την GreenCard και τα μέλη της attackBonus, defenseBonus, minimumHonor, effectBonus, effectCost.
        • Constructor της GreenCard: Το πεδίο cardText αρχικοποιείται από φράσεις του αρχείου CardTextes.txt.

    2. Follower.hpp, Item.hpp, Holding.hpp, Personality.hpp/Personality.cpp
        Τα πεδία τους αρχικοποιύνται ανάλογα το type τους με τις τιμές που έχουν δοθεί στα βοηθητικά αρχεία της εργασίας Followers_and_Weapons.txt και Personalities_and_Holdings.txt

    3. Player.hpp/ Player.cpp
        • 
        • 
        • 
        ...
        • battlePhase:

    4. GameBoard.hpp/GameBoard.cpp
        • initializeGameBoard:
            Ως όρισμα δίνεται ο αριθμός των παιχτών καθώς το πλήθος των διάφορων κατηγοριών καρτών που επιτρέπεται να έχουν στην κατοχή τους οι παίχτες ορίζεται από το βοηθητικό αρχείο DeckBuilder.hpp που δόθηκε.
        • checkWinningCondition:
            Η συνάρτηση ελέγχει τον αριθμό των επαρχιών κάθε παίχτη. Σε περίπτωση που έχουν καταστραφεί οι επαρχίες όλων των παιχτών εκτός από έναν, αυτός είναι ο νικητής και επιστρέφεται η σειρά προτεραιότητας παιξίματός του. Διαφορετικά, η συνάρτηση επιστρέφει -1.
        • gameplay:
            Εκτελούνται γύροι μέχρι να βρεθεί νικητής. Κάθε φάση εκτελείται από όλους τους παίχτες σύμφωνα με τη σειρά προτεραιότητας. Αν έχουν καταστραφεί όλες οι επαρχίες ενός παίχτη σημαίνει ότι έχει χάσει, επομένως δεν συμμετέχει στις φάσεις παιχνιδιού. Η checkWinningCondition εκτελείται μετά από κάθε Battle Phase.