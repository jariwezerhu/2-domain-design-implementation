Domain Design & Implementatie opdracht voor Adaptive Programming.

10-04-2023

Jari Wezer

Ik heb de "moeilijke" versie gebruikt, met polymorphisme.
Ik heb besloten om bij het maken van een task, de standaardwaarden te gebruiken dat er geen forklift certificate nodig is, en dat de task nog gedaan moet worden. Bij rearrangeShelf heb ik als standaardwaarde dat er wel een forklift certificate nodig is.
Ik heb ook een sortPallets() functie toegevoegd aan de shelf class. Ik heb hiervoor een bubble sort gebruikt, voor simpliciteit. Ook gebruikt het een real-life logica, waar de pallets eerst uit de shelf moeten worden gehaald en daarna weer geplaatst moeten worden. Verder heb ik een hasItem(itemName) toegevoegd aan de container class, zodat ik niet steeds door alle pallets hoef te iteraten.
Ik heb een getItemCount() toegevoegd aan de shelf class om het aantal van een bepaald item in die shelf te krijgen.
Ook een taskID toegevoegd aan Task class, voor performTask.

PerformTask werkt als volgt:
Als een task op todo staat, wordt hij uitgevoerd. Als deze succesvol is, wordt het finished;
Als hij faalt, wordt het failed.

Als een task op failed staat, wordt hij op todo gezet.