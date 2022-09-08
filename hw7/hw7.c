/**
 * @file hw7.c
 * @author JP
 * @collaborators NAMES OF PEOPLE THAT YOU COLLABORATED WITH HERE
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2022-03-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of Animal structs
struct animal animals[MAX_ANIMAL_LENGTH];

int size = 0;

/** addAnimal
 *
 * @brief creates a new Animal and adds it to the array of Animal structs, "animals"
 *
 *
 * @param "species" species of the animal being created and added
 *               NOTE: if the length of the species (including the null terminating character)
 *               is above MAX_SPECIES_LENGTH, truncate species to MAX_SPECIES_LENGTH. If the length
 *               is 0, return FAILURE.  
 *               
 * @param "id" id of the animal being created and added
 * @param "hungerScale" hunger scale of the animal being created and added
 * @param "habitat" habitat of the animal being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "species" length is 0
 *         (2) "habitat" length is 0
 *         (3) adding the new animal would cause the size of the array "animals" to
 *             exceed MAX_ANIMAL_LENGTH
 *        
 */
int addAnimal(const char *species, int id, double hungerScale, const char *habitat)
{
  UNUSED_PARAM(species);
  UNUSED_PARAM(id);
  UNUSED_PARAM(hungerScale);
  UNUSED_PARAM(habitat);

  if (my_strlen(species) == 0 || my_strlen(habitat) == 0 || size >= MAX_ANIMAL_LENGTH) {
    return FAILURE;
  }

  struct animal newAnimal;

  my_strncpy((&newAnimal) -> species, species, MAX_SPECIES_LENGTH - 1);
  newAnimal.id = id;
  newAnimal.hungerScale = hungerScale;
  my_strncpy((&newAnimal) -> habitat, habitat, MAX_HABITAT_LENGTH - 1);

  //animals[size] = newAnimal;
  my_strncpy((animals + size) -> species, species, MAX_SPECIES_LENGTH - 1);
  animals[size].id = newAnimal.id;
  animals[size].hungerScale = newAnimal.hungerScale;
  my_strncpy((animals + size) -> habitat, habitat, MAX_HABITAT_LENGTH - 1);

  size++;

  return SUCCESS;
}

/** updateAnimalSpecies
 *
 * @brief updates the species of an existing animal in the array of Animal structs, "animals"
 *
 * @param "animal" Animal struct that exists in the array "animals"
 * @param "species" new species of Animal "animal"
 *               NOTE: if the length of species (including the null terminating character)
 *               is above MAX_SPECIES_LENGTH, truncate species to MAX_SPECIES_LENGTH
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the Animal struct "animal" can not be found in the array "animals" based on its id
 */
int updateAnimalSpecies(struct animal animal, const char *species)
{
  UNUSED_PARAM(animal);
  UNUSED_PARAM(species);

  for (int i = 0; i < size; i++) {
    if (animals[i].id == animal.id) {
      my_strncpy(animals[i].species, species, MAX_SPECIES_LENGTH - 1);
      return SUCCESS;
    }
  }

  return FAILURE;
}

/** averageHungerScale
* @brief Search for all animals with the same species and find average the hungerScales
* 
* @param "species" Species that you want to find the average hungerScale for
* @return the average hungerScale of the specified species
*         if the species does not exist, return 0.0
*/
double averageHungerScale(const char *species)
{
  UNUSED_PARAM(species);
  double avg = 0.0;
  double num = 0.0;
  for (int i = 0; i < size; i++) {
    char *sp = (&animals[i]) -> species;
    if (my_strncmp(sp, species, my_strlen(sp)) == 0) {
      avg += animals[i].hungerScale;
      num++;
    }
  }
  if (num == 0) {
    return 0.0;
  }
  avg /= num;
  return avg;
}

/** swapAnimals
 *
 * @brief swaps the position of two Animal structs in the array of Animal structs, "animals"
 *
 * @param "index1" index of the first Animal struct in the array "animals"
 * @param "index2" index of the second Animal struct in the array "animals"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "animals"
 */
int swapAnimals(int index1, int index2)
{
  UNUSED_PARAM(index1);
  UNUSED_PARAM(index2);

  if (index1 < 0 || index2 < 0 || index1 >= size || index2 >= size) {
    return FAILURE;
  }

  struct animal a = animals[index1];
  animals[index1] = animals[index2];
  animals[index2] = a;

  return SUCCESS;
}

/** compareHabitat
 *
 * @brief compares the two Animals animals' habitats (using ASCII)
 *
 * @param "animal1" Animal struct that exists in the array "animals"
 * @param "animal2" Animal struct that exists in the array "animals"
 * @return negative number if animal1 is less than animal2, positive number if animal1 is greater
 *         than animal2, and 0 if animal1 is equal to animal2
 */
int compareHabitat(struct animal animal1, struct animal animal2)
{
  UNUSED_PARAM(animal1);
  UNUSED_PARAM(animal2);

  char *h1 = animal1.habitat;
  char *h2 = animal2.habitat;

  int l1 = my_strlen(animal1.habitat);
  int l2 = my_strlen(animal2.habitat);
  int max;
  if (l1 - l2 < 0) {
    max = l2;
  } else {
    max = l1;
  }

  return my_strncmp(h1, h2, max);
}

/** removeAnimal
 *
 * @brief removes Animal in the array of Animal structs, "animals", that has the same species
 *
 * @param "animal" Animal struct that exists in the array "animals"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the Animal struct "animal" can not be found in the array "animals"
 */
int removeAnimal(struct animal animal)
{
  UNUSED_PARAM(animal);

  for (int i = 0; i < size; i++) {
    char *sp = (&animals[i]) -> species;
    if (my_strncmp(sp, animal.species, my_strlen(sp)) == 0) {
      for (int j = i; j < size - 1; j++) {
        animals[j] = animals[j + 1];
      }
      size --;
      return SUCCESS;
    }    
  }

  return FAILURE;
}

/** sortAnimal
 *
 * @brief using the compareHabitat function, sort the Animals in the array of
 * Animal structs, "animals," by the animals' habitat
 * If two animals have the same habitat, place the hungier animal first
 *
 * @param void
 * @return void
 */
void sortAnimalsByHabitat(void)
{
  for (int i = 0; i < size; i++) {
    for (int j = i; j > 0; j--) {
      if (compareHabitat(animals[j], animals[j-1]) == 0) {
        double a = animals[j].hungerScale;
        double b = animals[j-1].hungerScale;
        if (a > b) {
          swapAnimals(j, j - 1);
        }
      }
      else if (compareHabitat(animals[j], animals[j-1]) < 0) {
        swapAnimals(j, j - 1);
      } else {
        break;
      }
    }
  }
}
