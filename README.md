# miniRT

Un **mini Ray Tracer** développé dans le cadre du cursus **42**.  
Le but est d’afficher des scènes 3D simples en respectant les bases du **ray tracing** (lancer de rayons), en utilisant uniquement **C** et **minilibX**.

---

## Objectifs du projet

- Comprendre les bases du **ray tracing** et du calcul de l’éclairage.
- Implémenter un moteur minimaliste capable de :
  - Générer une image à partir d’une scène décrite dans un fichier `.rt`.
  - Calculer les intersections rayon-objet.
  - Appliquer les lois de l’optique (ombres, lumière, réflexion simple).
- Utiliser **MiniLibX** pour afficher l’image et gérer les interactions.

---

## Fonctionnalités

- Lecture de fichiers de scène `.rt` :
  - Caméra(s)
  - Lumières
  - Objets (sphère, plan, cylindre, etc.)
- Calcul de l’éclairage :
  - Lumière ambiante
  - Lumières ponctuelles
  - Ombres
- Affichage via **MiniLibX** :
  - Fenêtre interactive
  - Navigation basique
- Gestion des **erreurs de parsing** (fichiers invalides).

---

## Compilation

```bash
make
```

Lancer le programme avec un fichier .rt :
```bash
./miniRT scenes/test.rt
``
