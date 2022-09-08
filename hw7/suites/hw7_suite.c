/**
 * @file hw7_suite.c
 * @author Alice, Corey, Nick
 * @brief Testing Suites to HW7 - Fall 2021
 * @date 2021-09-19
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

#define NO_STRING_H 2200
#define HW7_C_NOT_FOUND 1
#define HW7_FAILURE 2
#define STRING_H_USED 3
#define STRINGS_H_USED 4

#define INCORRECT_RESULT_MSG "array at index %d not populated correctly. Expected: %s, %d, %d (in order).\nargv[1]='%s'\n"

// This is the variable that determines if they used illegal stuff @see whatIsA2110StudentDoingHere()
static int dontReverseEngineerBro = NO_STRING_H;

// Helper function prototypes
static void setup(void);
static void _add_animal(const char *nickname, int pokedexNumber, double powerLevel, const char *speciesName);
static int whatIsA2110StudentDoingHere(void);


///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************* TESTS ***********************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/* addAnimal() tests */
// Test that catchPokemon works when called once (this is the "basic" intro test, easy test case)
START_TEST(test_addAnimal_single)
{
    // Step 1: the setup() function is called automagically
    // We don't really need to change it, all it does is clear the pokedex, set size=0 and detect illegal #includes

    // Step 2: per-test setup
    // If we want to do anything particular for this test (maybe have some data already in the pokedex, we should add it here)
    // It's fine if we start from an empty pokedex for this test, so nothing needed here either
    // Frequently, we have helper methods to help with setup. Check out the _catch_pokemon function; this is
    //   entirely separate from the student's catchPokemon function and is essentially a "working" implementation
    //   (without error handling) that you can use to add test data to the pokedex.

    // Step 3: make the function call we're testing (in this case, catchPokemon)
    const char *species = "Human";
    const int id = 0;
    const double hungerScale = 6.5;
    const char *habitat = "Earth";
    int retVal = addAnimal(species, id, hungerScale, habitat);

    // Step 4: Test that the return value is correct
    // If the first parameter is false, then the autograder test case will fail and print the message
    // If the first parameter is true, then it'll just keep going
    ck_assert_msg(retVal == SUCCESS, "Expected return value to be SUCCESS (%d) when inserting into empty Animals, got %d", SUCCESS, retVal);

    // Step 5: Make sure the internal state is correct
    // This function updates the pokedex, so we should make sure that the correct values were inserted
    // You should also check that the other entries already in the pokedex aren't deleted (there aren't an y in this case)
    // For other functions that don't update the pokedex, you would still want to check that didn't accidentally get changed
    // We don't need to test that the values at nickname and speciesName haven't changed, since they are pointers to const chars
    //printf("\n%s %d %f %s\n", species, id, hungerScale, habitat);
    //printf("%s %d %f %s\n\n", animals[0].species, animals[0].id, animals[0].hungerScale, animals[0].habitat);
    ck_assert_msg(size == 1, "Expected size to be 1 after inserting into empty Animals, was %d", size);
    ck_assert_msg(strncmp(animals[0].species, species, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", species, animals[0].species);
    ck_assert_msg(animals[0].id == id, "Expected id to be %d, was %d", id, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[0].habitat);
}
END_TEST // if you get weird compiler error messages, you probably forgot the END_TEST

// Now, repeat the process above until the function is fully tested.
// Make sure you test all "regular" cases (if the pokedex is empty, if there are already entries, etc.) as well as
//  also testing the edge cases (if the name is longer than the max length, if the species name is longer than the
//  max length, if both of those are true, etc.)

START_TEST(test_addAnimal_multiple_1) {
    const char *species1 = "Human";
    const int id1 = 0;
    const double hungerScale1 = 6.5;
    const char *habitat1 = "Earth";
    int retVal1 = addAnimal(species1, id1, hungerScale1, habitat1);

    const char *species2 = "Horse";
    const int id2 = 1;
    const double hungerScale2 = 2.3;
    const char *habitat2 = "Farm";
    int retVal2 = addAnimal(species2, id2, hungerScale2, habitat2);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);

    ck_assert_msg(size == 2, "Expected size to be 2 after inserting into Animals, was %d", size);

    ck_assert_msg(strncmp(animals[0].species, species1, MAX_SPECIES_LENGTH) == 0, "Animal species not set correctly");
    ck_assert_msg(animals[0].id == id1, "Animal ID not set correctly");
    ck_assert_msg(animals[0].hungerScale == hungerScale1, "Expected hungerScale to be %f, was %f", hungerScale1, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat1, MAX_HABITAT_LENGTH) == 0, "Animal habitat not set correctly");

    ck_assert_msg(strncmp(animals[1].species, species2, MAX_SPECIES_LENGTH) == 0, "Animal species not set correctly");
    ck_assert_msg(animals[1].id == id2, "Animal ID not set correctly");
    ck_assert_msg(animals[1].hungerScale == hungerScale2, "Expected hungerScale to be %f, was %f", hungerScale2, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, habitat2, MAX_HABITAT_LENGTH) == 0, "Animal habitat not set correctly");
}
END_TEST

START_TEST(test_addAnimal_multiple_2) {
    for (int i = 0; i < 25; i++) {
        // Deterministically generate animals
        char species[10];
        sprintf(species, "sp%d", i);
        int id = i;
        double hungerScale = (i*3)/10;
        char habitat[10];
        sprintf(habitat, "place%d", i);

        int retVal = addAnimal(species, id, hungerScale, habitat);
        ck_assert_int_eq(retVal, SUCCESS);
    }

    ck_assert_int_eq(size, 25);

    // Check the backing array after ALL students have been inserted
    for (int i = 0; i < 25; i++) {
        char species[10];
        sprintf(species, "sp%d", i);
        int id = i;
        double hungerScale = (i*3)/10;
        char habitat[10];
        sprintf(habitat, "place%d", i);

        ck_assert_msg(strncmp(animals[i].species, species, MAX_SPECIES_LENGTH) == 0, "Animal species expected %s but was %s", species, animals[i].species);
        ck_assert_msg(animals[i].id == id, "Animal ID expected %d but was %d", id, animals[i].id);
        ck_assert_msg(animals[i].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[i].hungerScale);
        ck_assert_msg(strncmp(animals[i].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Animal habitat not set correctly");
    }
}
END_TEST


//Test checks if null-terminator is inserted correctly
START_TEST(test_addAnimal_null_terminator) {
    _add_animal("biggest pokemon ever", 45, 4.0, "BulbasaurIvysaurVenusaur");
    size--;

    const char *species = "Terry";
    int id = 20;
    double hungerScale = 3.5;
    const char *habitat = "ShortID";
    int retVal = addAnimal(species, id, hungerScale, habitat);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);

    ck_assert_msg(strncmp(animals[0].species, species, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", species, animals[0].species);
    ck_assert_msg(animals[0].id == id, "Expected id to be %d, was %d", id, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[0].habitat);

}
END_TEST


// Test check for truncation
START_TEST(test_addAnimal_long_species)
{
    const char *species = "Ms. Elizabeth S. Longname III"; // This nickname should get truncated appropriately, do not expect failure
    const char* truncatedSpecies = "Ms. Eliza";
    int id = 21;
    double hungerScale = 4.5;
    const char *habitat = "Forest";
    int retVal = addAnimal(species, id, hungerScale, habitat);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);
    ck_assert_msg(strncmp(animals[0].species, truncatedSpecies, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", truncatedSpecies, animals[0].species);
    ck_assert_msg(animals[0].id == id, "Expected id to be %d, was %d", id, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[0].habitat);

}
END_TEST




/* **************** SHOULD BE DELETED?? *******************/

/*
START_TEST(test_catchPokemon_short_speciesName)
{
    const char *nickname = "Jerry";
    int pokedexNumber = 6;
    double powerLevel = 4.0;
    const char *speciesName = "C";
    int retVal = catchPokemon(nickname, pokedexNumber, powerLevel, speciesName);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST



START_TEST(test_catchPokemon_duplicate_pokemon)
{
    const char *nickname = "Udit";
    int pokedexNumber = 150;
    double powerLevel = 45.0;
    const char *speciesName1 = "Mew";
    const char *speciesName2 = "MewTwo";
    _add_pokemon(nickname, pokedexNumber, powerLevel, speciesName1);
    int retVal = catchPokemon(nickname, pokedexNumber+1, powerLevel-0.5, speciesName2); // Should flag as a duplicate based on nickname only

    ck_assert_int_eq(retVal, FAILURE);

    // The student we inserted manually should remain unchanged
    ck_assert_int_eq(size, 1);

    ck_assert(strncmp(pokedex[0].nickname, nickname, MAX_NICKNAME_SIZE) == 0);
    ck_assert_int_eq(pokedex[0].pokedexNumber, pokedexNumber);
    ck_assert(pokedex[0].powerLevel == powerLevel);
    ck_assert(strncmp(pokedex[0].speciesName, speciesName1, MAX_SPECIESNAME_SIZE) == 0);
}
END_TEST

*/


START_TEST(test_addAnimal_too_many_animals) {
    for (int i = 0; i < MAX_ANIMAL_SIZE; i++) {
        // Deterministically generate students
        char species[7];
        sprintf(species, "%02d", i);
        int id = 18 + i;
        double hungerScale = 20.0 - i / 4.0;
        char habitat[8];
        sprintf(habitat, "%02d", i);

        _add_animal(species, id, hungerScale, habitat);
    }

    int retVal = addAnimal("One Mohr", 100, 2.0, "HOUSE");
    ck_assert_int_eq(retVal, FAILURE);

    ck_assert_int_eq(size, MAX_ANIMAL_SIZE);

    // The students we inserted manually should remain unchanged
    for (int i = 0; i < MAX_ANIMAL_SIZE; i++) {
        char species[7];
        sprintf(species, "%02d", i);
        int id = 18 + i;
        double hungerScale = 20.0 - i / 4.0;
        char habitat[8];
        sprintf(habitat, "%02d", i);


        ck_assert_msg(strncmp(animals[i].species, species, MAX_SPECIES_LENGTH) == 0, "Animal species expected %s but was %s", species, animals[i].species);
        ck_assert_msg(animals[i].id == id, "Animal ID expected %d but was %d", id, animals[i].id);
        ck_assert_msg(animals[i].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[i].hungerScale);
        ck_assert_msg(strncmp(animals[i].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Animal habitat not set correctly");

    }
}
END_TEST

// --------------------------------------------------
/* updateAnimalSpecies tests */
// --------------------------------------------------

START_TEST(test_updateAnimalSpecies_basic) {
    // The only thing that matters is the species
    const char *sp1 = "Arthur";
    const char *sp2 = "Molly";
    const char *sp3 = "Fred";
    const char *sp4 = "George";
    int id1 = 20;
    int id2 = 11;
    double hungerScale = 6.8;
    const char *habitat = "Slowbro";

    // Even if the only difference is species, it should work
    _add_animal(sp1, id1, hungerScale, habitat);
    _add_animal(sp2, id2, hungerScale, habitat);

    int retVal1 = updateAnimalSpecies(animals[0], sp3);

    // The id is the only part of the struct that actually matters when we're searching
    // Make sure the students aren't checking using the whole struct
    struct animal search = animals[1];
    strcpy(search.species, "Slytherin");
    search.hungerScale -= 2;
    strcpy(search.habitat, "Slytherin");
    int retVal2 = updateAnimalSpecies(search, sp4);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);
    ck_assert_int_eq(size, 2);

    ck_assert_msg(strncmp(animals[0].species, sp3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", sp3, animals[0].species);
    ck_assert_msg(animals[0].id == id1, "Expected id to be %d, was %d", id1, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[0].habitat);


    ck_assert_msg(strncmp(animals[1].species, sp4, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", sp4, animals[1].species);
    ck_assert_msg(animals[1].id == id2, "Expected id to be %d, was %d", id2, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[1].habitat);

}
END_TEST

START_TEST(test_updateAnimalSpecies_long) {
    const char *species = "Mr. Jonathan G. Longname IV"; // This species should get truncated appropriately, do not expect failure
    const char *truncatedSpecies = "Mr. Jonat";
    const char *oldSpecies = "Misty";
    int id = 18;
    double hungerScale = 3.3;
    const char *habitat = "Pidgeot";
    _add_animal(oldSpecies, id, hungerScale, habitat);
    int retVal = updateAnimalSpecies(animals[0], species);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);

    ck_assert_msg(strncmp(animals[0].species, truncatedSpecies, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", truncatedSpecies, animals[0].species);
    ck_assert_msg(animals[0].id == id, "Expected id to be %d, was %d", id, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == hungerScale, "Expected hungerScale to be %f, was %f", hungerScale, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, habitat, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", habitat, animals[0].habitat);

}
END_TEST

START_TEST(test_updateAnimalSpecies_failure) {
    for (int i = 0; i < 15; i++) {
        // Deterministically generate students
        char species[7];
        sprintf(species, "Prof %d", i);
        int id = 18 + i;
        double hungerScale = 4.0 - i/10;
        char habitat[9];
        sprintf(habitat, "ABCD00%d", i);

        _add_animal(species, id, hungerScale, habitat);
    }

    ck_assert_int_eq(size, 15);

    const char *species = "Sips";
    int id = 2;
    double hungerScale = 10.0;
    const char *habitat = "ekans";

    struct animal search;
    strcpy(search.species, species);
    search.id = id;
    search.hungerScale = hungerScale;
    strcpy(search.habitat, habitat);

    int retVal = updateAnimalSpecies(search, "Shnape");

    ck_assert_int_eq(retVal, FAILURE);
}
END_TEST

START_TEST(test_updateAnimalSpecies_empty_array) {
    const char *species = "Luna";
    int id = 20;
    double hungerScale = 3.6;
    const char *habitat = "Raticate";

    _add_animal(species, id, hungerScale, habitat);
    size--; // This entry isn't actually in the array!

    int retVal = updateAnimalSpecies(animals[0], "Cedric");

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

// ---------------------------------------------------------
/* swapAnimal tests */
// ---------------------------------------------------------

/*
    nickname => species
    pokedexNumber => id
    powerLevel => hungerScale
    speciesname => habitat
*/
START_TEST(test_swapAnimal_basic) {
    int index1 = 0;
    int index2 = 2;

    const char *nickname1 = "Alice";
    const char *nickname2 = "Nick";
    const char *nickname3 = "Shawn";
    const char *nickname4 = "Kevin";
    int pokedexNumber = 1;
    int pokedexNumber2 = 4;
    double powerLevel = 3.3;
    const char *speciesName = "Bulbasaur";
    const char *speciesName2 = "Charmander";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber2, powerLevel, speciesName2);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName);

    int retVal = swapAnimals(index1, index2);
    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    //index 1 = index2

    ck_assert_msg(strncmp(animals[index1].species, nickname3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname3, animals[index1].species);
    ck_assert_msg(animals[index1].id == pokedexNumber2, "Expected id to be %d, was %d", pokedexNumber2, animals[index1].id);
    ck_assert_msg(animals[index1].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[index1].hungerScale);
    ck_assert_msg(strncmp(animals[index1].habitat, speciesName2, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName2, animals[index1].habitat);

    //index2 = index1

    ck_assert_msg(strncmp(animals[index2].species, nickname1, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname1, animals[index2].species);
    ck_assert_msg(animals[index2].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[index2].id);
    ck_assert_msg(animals[index2].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[index2].hungerScale);
    ck_assert_msg(strncmp(animals[index2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[index2].habitat);

    ck_assert_msg(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname2, animals[1].species);
    ck_assert_msg(animals[1].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[1].habitat);

    ck_assert_msg(strncmp(animals[3].species, nickname4, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname4, animals[3].species);
    ck_assert_msg(animals[3].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[3].id);
    ck_assert_msg(animals[3].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[3].hungerScale);
    ck_assert_msg(strncmp(animals[3].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[3].habitat);

}
END_TEST

START_TEST(test_swapAnimal_same) {
    const char *nickname1 = "Nick";
    const char *nickname2 = "Mick";
    const char *nickname3 = "Tim";
    const char *nickname4 = "YOLO";
    int pokedexNumber = 2;
    int pokedexNumber2 = 8;
    double powerLevel = 3.3;
    const char *speciesName = "Ivysaur";
    const char *speciesName2 = "Wartortle";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber2, powerLevel, speciesName2);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName);

    int retVal = swapAnimals(1, 1);

    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    ck_assert_msg(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname1, animals[0].species);
    ck_assert_msg(animals[0].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[0].habitat);


    ck_assert_msg(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname2, animals[1].species);
    ck_assert_msg(animals[1].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[1].habitat);


    ck_assert_msg(strncmp(animals[2].species, nickname3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname3, animals[2].species);
    ck_assert_msg(animals[2].id == pokedexNumber2, "Expected id to be %d, was %d", pokedexNumber2, animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName2, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName2, animals[2].habitat);


    ck_assert_msg(strncmp(animals[3].species, nickname4, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname4, animals[3].species);
    ck_assert_msg(animals[3].id == pokedexNumber, "Expected id to be %d, was %d", pokedexNumber, animals[3].id);
    ck_assert_msg(animals[3].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[3].hungerScale);
    ck_assert_msg(strncmp(animals[3].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[3].habitat);


}
END_TEST

START_TEST(test_swapAnimal_index_out_of_bounds_1) {
    int index1 = -2; //out of bounds
    int index2 = 2;

    const char *nickname1 = "Luna";
    const char *nickname2 = "squid";
    const char *nickname3 = "game";
    const char *nickname4 = "Nick";
    int pokedexNumber = 7;
    double powerLevel = 3.3;
    const char *speciesName = "Squirtle";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName);

    int retVal = swapAnimals(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[0].id, pokedexNumber);
    ck_assert(animals[0].hungerScale == powerLevel);
    ck_assert(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[1].id, pokedexNumber);
    ck_assert(animals[1].hungerScale == powerLevel);
    ck_assert(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[2].species, nickname3, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[2].id, pokedexNumber);
    ck_assert(animals[2].hungerScale == powerLevel);
    ck_assert(strncmp(animals[2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[3].species, nickname4, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[3].id, pokedexNumber);
    ck_assert(animals[3].hungerScale == powerLevel);
    ck_assert(strncmp(animals[3].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);
}
END_TEST

START_TEST(test_swapAnimal_index_out_of_bounds_2) {
    int index1 = 1;
    int index2 = 5; //out of bounds

    const char *nickname1 = "sparkey";
    const char *nickname2 = "fly";
    const char *nickname3 = "Aang";
    const char *nickname4 = "naruto";
    int pokedexNumber = 21;
    double powerLevel = 3.3;
    const char *speciesName = "Spearow";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName);

    int retVal = swapAnimals(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[0].id, pokedexNumber);
    ck_assert(animals[0].hungerScale == powerLevel);
    ck_assert(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[1].id, pokedexNumber);
    ck_assert(animals[1].hungerScale == powerLevel);
    ck_assert(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[2].species, nickname3, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[2].id, pokedexNumber);
    ck_assert(animals[2].hungerScale == powerLevel);
    ck_assert(strncmp(animals[2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[3].species, nickname4, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[3].id, pokedexNumber);
    ck_assert(animals[3].hungerScale == powerLevel);
    ck_assert(strncmp(animals[3].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);
}
END_TEST

START_TEST(test_swapAnimal_index_out_of_bounds_3) {
    int index1 = 1;

    const char *nickname1 = "Pika";
    const char *nickname2 = "Bill";
    const char *nickname3 = "Thor";
    const char *nickname4 = "Art";
    int pokedexNumber = 26;
    double powerLevel = 3.3;
    const char *speciesName = "Raichu";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName);

    int index2 = size; //out of bounds

    int retVal = swapAnimals(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[0].id, pokedexNumber);
    ck_assert(animals[0].hungerScale == powerLevel);
    ck_assert(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[1].id, pokedexNumber);
    ck_assert(animals[1].hungerScale == powerLevel);
    ck_assert(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[2].species, nickname3, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[2].id, pokedexNumber);
    ck_assert(animals[2].hungerScale == powerLevel);
    ck_assert(strncmp(animals[2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);

    ck_assert(strncmp(animals[3].species, nickname4, MAX_SPECIES_LENGTH) == 0);
    ck_assert_int_eq(animals[3].id, pokedexNumber);
    ck_assert(animals[3].hungerScale == powerLevel);
    ck_assert(strncmp(animals[3].habitat, speciesName, MAX_HABITAT_LENGTH) == 0);
}
END_TEST


// ---------------------------------------------------------
/* removeAnimal tests */
// ---------------------------------------------------------
START_TEST(test_removeAnimal_basic_1) {

    const char *nickname1 = "Sam";
    const char *nickname2 = "Matt";
    const char *nickname3 = "Amanda";
    const char *nickname4 = "Chris";
    int id1 = 28;
    int id2 = 8;
    int id3 = 18;
    int id4 = 6;
    double powerLevel = 20.3;
    const char *speciesName = "Sandslash";

    _add_animal(nickname1, id1, powerLevel, speciesName);
    _add_animal(nickname2, id2, powerLevel, speciesName); //student being removed
    _add_animal(nickname3, id3, powerLevel, speciesName);
    _add_animal(nickname4, id4, powerLevel, speciesName);

    int retVal = removeAnimal(animals[1]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_msg(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname1, animals[0].species);
    ck_assert_msg(animals[0].id == id1, "Expected id to be %d, was %d", id1, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[0].habitat);

    ck_assert_msg(strncmp(animals[1].species, nickname3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname3, animals[1].species);
    ck_assert_msg(animals[1].id == id3, "Expected id to be %d, was %d", id3, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[1].habitat);

    ck_assert_msg(strncmp(animals[2].species, nickname4, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname4, animals[2].species);
    ck_assert_msg(animals[2].id == id4, "Expected id to be %d, was %d", id4, animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[2].habitat);

}
END_TEST

START_TEST(test_removeAnimal_basic_2) {

    const char *nickname1 = "thia";
    const char *nickname2 = "gary";
    const char *nickname3 = "Rock";
    const char *nickname4 = "Chris";
    int id1 = 2;
    int id2 = 8;
    int id3 = 18;
    int id4 = 6;
    double powerLevel = 13.3;
    const char *speciesName = "Meowth";

    _add_animal(nickname1, id1, powerLevel, speciesName);
    _add_animal(nickname2, id2, powerLevel, speciesName);
    _add_animal(nickname3, id3, powerLevel, speciesName);
    _add_animal(nickname4, id4, powerLevel, speciesName); //student being removed

    int retVal = removeAnimal(animals[3]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_msg(strncmp(animals[0].species, nickname1, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname1, animals[0].species);
    ck_assert_msg(animals[0].id == id1, "Expected id to be %d, was %d", id1, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[0].habitat);


    ck_assert_msg(strncmp(animals[1].species, nickname2, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname2, animals[1].species);
    ck_assert_msg(animals[1].id == id2, "Expected id to be %d, was %d", id2, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[1].habitat);


    ck_assert_msg(strncmp(animals[2].species, nickname3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname3, animals[2].species);
    ck_assert_msg(animals[2].id == id3, "Expected id to be %d, was %d", id3, animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel, "Expected hungerScale to be %f, was %f", powerLevel, animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName, animals[2].habitat);

}
END_TEST

START_TEST(test_removeAnimal_animal_does_not_exist) {
    const char *nickname1 = "Nemul";
    const char *nickname2 = "Nadir";
    const char *nickname3 = "Toast";
    const char *nickname4 = "Char";
    int pokedexNumber = 54;
    double powerLevel = 33.3;
    const char *speciesName = "Psyduck";

    _add_animal(nickname1, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname2, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname3, pokedexNumber, powerLevel, speciesName);
    _add_animal(nickname4, pokedexNumber, powerLevel, speciesName); 


    const char *name5 = "Paul";
    int pokedexNumber2 = 60;
    double powerLevel2 = 3.35;
    const char *speciesName2 = "Poliwag";

    struct animal s;
    strcpy(s.species, name5);
    s.id = pokedexNumber2;
    s.hungerScale = powerLevel2;
    strcpy(s.habitat, speciesName2);

    int retVal = removeAnimal(s);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

}
END_TEST

START_TEST(test_removeAnimal_empty_array) {
    const char *nickname = "Astro";
    int pokedexNumber = 65;
    double powerLevel = 0.0;
    const char *speciesName = "Alakazam";

    _add_animal(nickname, pokedexNumber, powerLevel, speciesName);
    size--; // This entry doesn't actually exist in the array!

    int retVal = removeAnimal(animals[0]);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST



//----------------------------------------
/* compareAnimaltests */
// Compares through habitat 
// hungerScale for tie-breaking
//----------------------------------------

START_TEST(test_compareAnimal_basic_equal) {
    const char *species = "Jeff";
    int id = 77;
    double hunger1 = 3.38;
    double hunger2 = 3.90;
    const char *hab1 = "Ponyta";
    const char *hab2 = "Ponyta";

    // Same habitat
    _add_animal(species, id, hunger1, hab1);
    _add_animal(species, id, hunger2, hab2);

    int retVal = compareHabitat(animals[0], animals[1]);

    ck_assert_int_eq(retVal, 0);
}
END_TEST


START_TEST(test_compareAnimal_basic_less_than_1) {
    const char *species1 = "Jeff";
    const char *species2 = "Victor";
    int id = 77;
    double hunger1 = 3.38;
    double hunger2 = 3.90;
    const char *hab1 = "Ponyta";
    const char *hab2 = "Raichu";

    // hab1 < hab2
    _add_animal(species1, id, hunger1, hab1);
    _add_animal(species2, id, hunger2, hab2);


  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST

START_TEST(test_compareAnimal_basic_less_than_2) {
  const char *nickname1 = "Geo";
  const char *nickname2 = "Jelly";
  int pokedexNumber1 = 70;
  int pokedexNumber2 = 72;
  double powerLevel1 = 20.88;
  double powerLevel2 = 13.11;
  const char *speciesName1 = "Geodude";
  const char *speciesName2 = "Tentacool";

  // habitat1< habitat2
  _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
  _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);

  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST

START_TEST(test_compareAnimal_basic_greater_than_1) {
  const char *nickname1 = "Vic";
  const char *nickname2 = "Nick";
  int pokedexNumber1 = 80;
  int pokedexNumber2 = 79;
  double powerLevel1 = 14.88;
  double powerLevel2 = 13.11;
  const char *speciesName1 = "Tentacool";
  const char *speciesName2 = "Slowbro";

  //habitat1 > habitat2
  _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
  _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);

  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

START_TEST(test_compareAnimal_basic_greater_than_2) {
  const char *nickname1 = "vic";
  const char *nickname2 = "plant_boy";
  int pokedexNumber1 = 70;
  int pokedexNumber2 = 71;
  double powerLevel1 = 2.88;
  double powerLevel2 = 3.11;
  const char *speciesName1 = "Victreebel";
  const char *speciesName2 = "Geodude";

  _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
  _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);

  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

//********* ADD TESTS FOR SAME HABITAT, DIFFERENT HUNGER LEVEL ************
/*START_TEST(test_compareAnimal_same_habitat1){

const char *nickname1 = "vic";
  const char *nickname2 = "plant_boy";
  int pokedexNumber1 = 1;
  int pokedexNumber2 = 71;
  double powerLevel1 = 2.0;
  double powerLevel2 = 3.11;
  const char *speciesName1 = "Earth";
  const char *speciesName2 = "Earth";

  // animals[0] < animals[1]
  _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
  _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);

  //retVal should be < 0
  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_lt(retVal, 0);

}
END_TEST

START_TEST(test_compareAnimal_same_habitat2){

const char *nickname1 = "vic";
  const char *nickname2 = "plant_boy";
  int pokedexNumber1 = 1;
  int pokedexNumber2 = 71;
  double powerLevel1 = 4.0;
  double powerLevel2 = 3.11;
  const char *speciesName1 = "Earth";
  const char *speciesName2 = "Earth";

  // animals[0] > animals[1]
  _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
  _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);

  //retVal should be < 0
  int retVal = compareHabitat(animals[0], animals[1]);

  ck_assert_int_gt(retVal, 0);

}
END_TEST*/

/*
----------------------------------------------------------------------------------------------
------------------------------------- RESUME -------------------------------------------------
----------------------------------------------------------------------------------------------
*/

// -------------------------------
/* sortAnimal tests */
// --------------------------------
START_TEST(test_sortAnimal_1) {
    const char *nickname1 = "Maeve"; // sorted: 1
    const char *nickname2 = "Dave"; // sorted: 2
    const char *nickname3 = "Eve"; // sorted: 0
    int pokedexNumber1 = 20;
    int pokedexNumber2 = 23;
    int pokedexNumber3 = 19;
    double powerLevel1 = 2.77;
    double powerLevel2 = 2.94;
    double powerLevel3 = 3.98;
    const char *speciesName1 = "Forest";
    const char *speciesName2 = "Ocean";
    const char *speciesName3 = "Desert";

    _add_animal(nickname1, pokedexNumber1, powerLevel1, speciesName1);
    _add_animal(nickname2, pokedexNumber2, powerLevel2, speciesName2);
    _add_animal(nickname3, pokedexNumber3, powerLevel3, speciesName3);

    sortAnimalsByHabitat();

    ck_assert_int_eq(size, 3);

    ck_assert_msg(strncmp(animals[0].species, nickname3, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname3, animals[0].species);
    ck_assert_msg(animals[0].id == pokedexNumber3, "Expected id to be %d, was %d", pokedexNumber3, animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel3, "Expected hungerScale to be %f, was %f", powerLevel3, animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName3, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName3, animals[0].habitat);

    ck_assert_msg(strncmp(animals[1].species, nickname1, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname1, animals[1].species);
    ck_assert_msg(animals[1].id == pokedexNumber1, "Expected id to be %d, was %d", pokedexNumber1, animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel1, "Expected hungerScale to be %f, was %f", powerLevel1, animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName1, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName1, animals[1].habitat);

    ck_assert_msg(strncmp(animals[2].species, nickname2, MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname2, animals[2].species);
    ck_assert_msg(animals[2].id == pokedexNumber2, "Expected id to be %d, was %d", pokedexNumber2, animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel2, "Expected hungerScale to be %f, was %f", powerLevel2, animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName2, MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName2, animals[2].habitat);

}
END_TEST

START_TEST(test_sortAnimal_2) {
    const char *nickname[] = {"Neville", "Dean", "Seamus", "Lavender", "Parvati"};
              // sorted: {"Neville", "Lavender", "Dean", "Seamus", "Parvati"}
              //           0         3           1       2         4
    int pokedexNumber[] = {18, 21, 21, 19, 23};
    double powerLevel[] = {1.00, 3.42, 2.99, 3.56, 4.00};
    const char *speciesName[] = {
        "ABC",
        "HIJ",
        "DEF",
        "XYZ",
        "BCD"
    };
    for (int i = 0; i < 5; i++) {
        _add_animal(nickname[i], pokedexNumber[i], powerLevel[i], speciesName[i]);
    }

    sortAnimalsByHabitat();

    ck_assert_int_eq(size, 5);

    ck_assert_msg(strncmp(animals[0].species, nickname[0], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[0], animals[0].species);
    ck_assert_msg(animals[0].id == pokedexNumber[0], "Expected id to be %d, was %d", pokedexNumber[0], animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel[0], "Expected hungerScale to be %f, was %f", powerLevel[0], animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName[0], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[0], animals[0].habitat);

    ck_assert_msg(strncmp(animals[1].species, nickname[4], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[4], animals[1].species);
    ck_assert_msg(animals[1].id == pokedexNumber[4], "Expected id to be %d, was %d", pokedexNumber[4], animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel[4], "Expected hungerScale to be %f, was %f", powerLevel[4], animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName[4], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[4], animals[1].habitat);

    ck_assert_msg(strncmp(animals[2].species, nickname[2], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[2], animals[2].species);
    ck_assert_msg(animals[2].id == pokedexNumber[2], "Expected id to be %d, was %d", pokedexNumber[2], animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel[2], "Expected hungerScale to be %f, was %f", powerLevel[2], animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName[2], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[2], animals[2].habitat);

    ck_assert_msg(strncmp(animals[3].species, nickname[1], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[1], animals[3].species);
    ck_assert_msg(animals[3].id == pokedexNumber[1], "Expected id to be %d, was %d", pokedexNumber[1], animals[3].id);
    ck_assert_msg(animals[3].hungerScale == powerLevel[1], "Expected hungerScale to be %f, was %f", powerLevel[1], animals[3].hungerScale);
    ck_assert_msg(strncmp(animals[3].habitat, speciesName[1], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[1], animals[3].habitat);

    ck_assert_msg(strncmp(animals[4].species, nickname[3], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[3], animals[4].species);
    ck_assert_msg(animals[4].id == pokedexNumber[3], "Expected id to be %d, was %d", pokedexNumber[3], animals[4].id);
    ck_assert_msg(animals[4].hungerScale == powerLevel[3], "Expected hungerScale to be %f, was %f", powerLevel[3], animals[4].hungerScale);
    ck_assert_msg(strncmp(animals[4].habitat, speciesName[3], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[3], animals[4].habitat);
  
}
END_TEST

//Same Habitat
//SOrt by hungerScale
START_TEST(test_sortAnimal_3) {
    const char *nickname[] = {"Draco", "Vincent", "Gregory", "Blaise", "Theodore", "Pansy", "Millicant", "Daphne"};
    //           after removing last two:
    //           sorted: {"Blaise", "Draco", "Theodore", "Gregory", "Pansy", "Vincent"}
    //                     3        0        4           2          5        1
    int pokedexNumber[] = {18, 121, 73, 9, 18, 99, 118, 21};
    // HungerScale below
    double powerLevel[] = {8.00, //0
                           5.42, //3
                           6.99, //2
                           2.56, //4
                           7.50, //1
                           1.00, //5
                           2.3,
                            1.89};
    const char *speciesName[] = {
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
    };
    for (int i = 0; i < 8; i++) {
        _add_animal(nickname[i], pokedexNumber[i], powerLevel[i], speciesName[i]);
    }
    size -= 2; // Millicant and Daphne don't exist :(

    sortAnimalsByHabitat();

    ck_assert_int_eq(size, 6);

    ck_assert_msg(strncmp(animals[0].species, nickname[0], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[0], animals[0].species);
    ck_assert_msg(animals[0].id == pokedexNumber[0], "Expected id to be %d, was %d", pokedexNumber[0], animals[0].id);
    ck_assert_msg(animals[0].hungerScale == powerLevel[0], "Expected hungerScale to be %f, was %f", powerLevel[0], animals[0].hungerScale);
    ck_assert_msg(strncmp(animals[0].habitat, speciesName[0], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[0], animals[0].habitat);


    ck_assert_msg(strncmp(animals[1].species, nickname[4], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[4], animals[1].species);
    ck_assert_msg(animals[1].id == pokedexNumber[4], "Expected id to be %d, was %d", pokedexNumber[4], animals[1].id);
    ck_assert_msg(animals[1].hungerScale == powerLevel[4], "Expected hungerScale to be %f, was %f", powerLevel[4], animals[1].hungerScale);
    ck_assert_msg(strncmp(animals[1].habitat, speciesName[4], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[4], animals[1].habitat);

    ck_assert_msg(strncmp(animals[2].species, nickname[2], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[2], animals[2].species);
    ck_assert_msg(animals[2].id == pokedexNumber[2], "Expected id to be %d, was %d", pokedexNumber[2], animals[2].id);
    ck_assert_msg(animals[2].hungerScale == powerLevel[2], "Expected hungerScale to be %f, was %f", powerLevel[2], animals[2].hungerScale);
    ck_assert_msg(strncmp(animals[2].habitat, speciesName[2], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[2], animals[2].habitat);


   ck_assert_msg(strncmp(animals[3].species, nickname[1], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[1], animals[3].species);
    ck_assert_msg(animals[3].id == pokedexNumber[1], "Expected id to be %d, was %d", pokedexNumber[1], animals[3].id);
    ck_assert_msg(animals[3].hungerScale == powerLevel[1], "Expected hungerScale to be %f, was %f", powerLevel[1], animals[3].hungerScale);
    ck_assert_msg(strncmp(animals[3].habitat, speciesName[1], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[1], animals[3].habitat);

    
    ck_assert_msg(strncmp(animals[4].species, nickname[3], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[3], animals[4].species);
    ck_assert_msg(animals[4].id == pokedexNumber[3], "Expected id to be %d, was %d", pokedexNumber[3], animals[4].id);
    ck_assert_msg(animals[4].hungerScale == powerLevel[3], "Expected hungerScale to be %f, was %f", powerLevel[3], animals[4].hungerScale);
    ck_assert_msg(strncmp(animals[4].habitat, speciesName[3], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[3], animals[4].habitat);


    ck_assert_msg(strncmp(animals[5].species, nickname[5], MAX_SPECIES_LENGTH) == 0, "Expected species to be %s, was %s", nickname[5], animals[5].species);
    ck_assert_msg(animals[5].id == pokedexNumber[5], "Expected id to be %d, was %d", pokedexNumber[5], animals[5].id);
    ck_assert_msg(animals[5].hungerScale == powerLevel[5], "Expected hungerScale to be %f, was %f", powerLevel[5], animals[5].hungerScale);
    ck_assert_msg(strncmp(animals[5].habitat, speciesName[5], MAX_HABITAT_LENGTH) == 0, "Expected habitat name to be %s, was %s", speciesName[5], animals[5].habitat);

}
END_TEST

//----------------------------------
/* averageHungerScale tests */
//----------------------------------

START_TEST(test_averageHungerScale_basic) {

    double avg = 0.0;
    const char *species = "Human";
    const int id = 0;
    const double hungerScale = 7.2;
    const char *habitat = "Earth";

    for(int i = 0; i < 5; i ++) {
        avg += hungerScale;
        _add_animal(species, id, hungerScale, habitat);
    }

    avg /= 5;

    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(avg, averageHungerScale(species));
    ck_assert_msg(avg == averageHungerScale(species), "Average Hunger incorrect");
}
END_TEST

START_TEST(test_averageHungerScale_no_species) {
    double avg = 0.0;
    const char *species = "Human";
    const int id = 0;
    const double hungerScale = 1.0;
    const char *habitat = "Earth";

    for(int i = 0; i < 5; i ++) {
        avg += hungerScale;
        _add_animal(species, id, hungerScale, habitat);
    }


    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(0.0, averageHungerScale("no_species"));
    ck_assert_msg(0.0 == averageHungerScale("no_species"), "Average Hunger incorrect");
}
END_TEST

START_TEST(test_averageHungerScale_many_species) {

    const char *nickname[] = {"Neville", "Dean", "Seamus", "Lavender", "Parvati"};
              // sorted: {"Neville", "Lavender", "Dean", "Seamus", "Parvati"}
              //           0         3           1       2         4
    int pokedexNumber[] = {18, 21, 21, 19, 23};
    double powerLevel[] = {1.00, 3.42, 2.99, 3.56, 4.00};
    const char *speciesName[] = {
        "ABC",
        "HIJ",
        "DEF",
        "XYZ",
        "BCD"
    };
    for (int i = 0; i < 5; i++) {
        _add_animal(nickname[i], pokedexNumber[i], powerLevel[i], speciesName[i]);
    }

    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(powerLevel[1], averageHungerScale(nickname[1]));
    ck_assert_msg(powerLevel[1] == averageHungerScale(nickname[1]), "Average Hunger incorrect");

}
END_TEST

///////////////////////////////////////////////////////////////////////////////////////////////////
/************************************** HELPER FUNCTIONS *****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Wipe out the array - since they are globals, it is reasonable for students to expect the array to be zeroed and size to be 0 before each test
 * Also try to detect any funky stuff going on with including <string(s).h>
 */
static void setup(void)
{
    memset(animals, 0, sizeof(animals));
    size = 0;
    if (dontReverseEngineerBro != NO_STRING_H)
    {
        if (dontReverseEngineerBro == HW7_C_NOT_FOUND) {
            ck_abort_msg("ERROR: Can't open hw7.c");
        } else if (dontReverseEngineerBro == STRING_H_USED || dontReverseEngineerBro == STRINGS_H_USED) {
            ck_abort_msg("ALL TESTS FAILED: Using <string.h> is not allowed");
        } else {
            ck_abort_msg("ERROR: Illegal stuff used in hw7.c");
        }
    }
}

/**
 * Adds a student - doesn't deal with error cases, so be careful about what you pass in
 */
static void _add_animal(const char *species, int id, double hunger, const char *habitat) {

    strncpy(animals[size].species, species, my_strlen(species) + 1);
    animals[size].id = id;
    animals[size].hungerScale = hunger;
    strncpy(animals[size].habitat, habitat, my_strlen(habitat) + 1);
    size++;
}
/**
 * This file can be huge, let's trust student a little bit and make sure even if they do add additional libraries, they add it at the top
 * WARNING: this does not work on the entire file (@see counterLimit)
 *
 * @return int a status code (@see #defines at the top)
 */
static int whatIsA2110StudentDoingHere(void)
{
    FILE *hw7DotC = fopen("hw7.c", "r");
    if (!hw7DotC)
    {
        printf("ERROR: Can't open hw7.c\n\n");
        return HW7_C_NOT_FOUND;
    }

    char buffer[512]; // Should not have code lines more than this size --> This could result in a bug if anybody bypasses this length
    int insideMultiFlag = 0; // Boolean flag for whether we're currently inside a /* */ multi-line comment

    // only checking the first 200 lines
    int counterLimit = 200;

    // Checking for disallowed stuff
    while (!feof(hw7DotC) && --counterLimit)
    {
        if (fgets(buffer, sizeof(buffer), hw7DotC))
        {
            char *i = buffer;
            // traverse buffer (current line) in case of multiple multi-line comments on same line
            while (i && *i)
            {
                char *nextI = NULL; // nextI is what i is set to on the next iteration (used as a delayed break in some cases)

                if (insideMultiFlag) {
                    // if in a multi-line commment, ignore everything until we reach a */
                    char *nextMultiEnd = strstr(i, "*/");
                    if (!nextMultiEnd) {
                        nextI = NULL; // we don't need to check rest of line because the multi-line comment doesn't end on this line
                    } else {
                        insideMultiFlag = 0;
                        nextI = nextMultiEnd + strlen("*/");
                    }
                } else {
                    // if we find a // comment first, the rest of the line will be commented, if a /* is first, the line will be commented until the next */
                    char *nextSingleStart = strstr(i, "//");
                    char *nextMultiStart = strstr(i, "/*");
                    char nonCommentChars[sizeof(buffer) / sizeof(char) + 1];

                    if ((!nextSingleStart && nextMultiStart) || ((nextSingleStart && nextMultiStart) && nextMultiStart < nextSingleStart)) {
                        // a /* */ comment starts at some point in this line
                        insideMultiFlag = 1;
                        nextI = nextMultiStart + strlen("/*");

                        // Grabbing everything from line to comment
                        int beforeCommentSize = (nextMultiStart - i);
                        strncpy(nonCommentChars, i, beforeCommentSize);
                        nonCommentChars[beforeCommentSize] = '\0';
                    } else if ((nextSingleStart && !nextMultiStart) || ((nextSingleStart && nextMultiStart) && nextSingleStart < nextMultiStart)) {
                        // rest of line is // comment
                        nextI = NULL;

                        // Grabbing everything from line to comment
                        int beforeCommentSize = (nextSingleStart - i);
                        strncpy(nonCommentChars, i, beforeCommentSize);
                        nonCommentChars[beforeCommentSize] = '\0';
                    } else {
                        // rest of line isn't a comment
                        nextI = NULL;

                        // Grab rest of line (buffer/i always ends with \0 because of fgets so we can strcpy)
                        strcpy(nonCommentChars, i);
                    }

                    if (strstr(nonCommentChars, "<string.h>"))
                    {
                        printf("ALL TESTS FAILED: Using <string.h> is not allowed\n\n");
                        return STRING_H_USED;
                    }

                    if (strstr(nonCommentChars, "<strings.h>"))
                    {
                        printf("ALL TESTS FAILED: (Trying to be sneaky huh?). Using <strings.h> is not allowed\n\n");
                        return STRINGS_H_USED;
                    }
                }

                i = nextI;
            }            
        }
    }

    // Nice one ese
    return NO_STRING_H;
}

Suite *hw7_suite(void)
{
    Suite *s = suite_create("hw7_suite");

    // Even if they bypass this, they still need a valid implementation
    dontReverseEngineerBro = whatIsA2110StudentDoingHere();

    tcase_hack(s, setup, NULL, test_addAnimal_single);
    tcase_hack(s, setup, NULL, test_addAnimal_multiple_1);
    tcase_hack(s, setup, NULL, test_addAnimal_multiple_2);
    tcase_hack(s, setup, NULL, test_addAnimal_null_terminator);
    tcase_hack(s, setup, NULL, test_addAnimal_long_species);
    //tcase_hack(s, setup, NULL, test_addAnimal_short_speciesName);
    //tcase_hack(s, setup, NULL, test_addAnimal_duplicate_pokemon);
    tcase_hack(s, setup, NULL, test_addAnimal_too_many_animals);

    tcase_hack(s, setup, NULL, test_updateAnimalSpecies_basic);
    tcase_hack(s, setup, NULL, test_updateAnimalSpecies_long);
    tcase_hack(s, setup, NULL, test_updateAnimalSpecies_failure);
    tcase_hack(s, setup, NULL, test_updateAnimalSpecies_empty_array);
    
    tcase_hack(s, setup, NULL, test_swapAnimal_basic);
    tcase_hack(s, setup, NULL, test_swapAnimal_same);
    tcase_hack(s, setup, NULL, test_swapAnimal_index_out_of_bounds_1);
    tcase_hack(s, setup, NULL, test_swapAnimal_index_out_of_bounds_2);
    tcase_hack(s, setup, NULL, test_swapAnimal_index_out_of_bounds_3);
    
    tcase_hack(s, setup, NULL, test_removeAnimal_basic_1);
    tcase_hack(s, setup, NULL, test_removeAnimal_basic_2);
    tcase_hack(s, setup, NULL, test_removeAnimal_animal_does_not_exist);
    tcase_hack(s, setup, NULL, test_removeAnimal_empty_array);
    
    tcase_hack(s, setup, NULL, test_compareAnimal_basic_equal);
    tcase_hack(s, setup, NULL, test_compareAnimal_basic_less_than_1);
    tcase_hack(s, setup, NULL, test_compareAnimal_basic_less_than_2);
    tcase_hack(s, setup, NULL, test_compareAnimal_basic_greater_than_1);
    tcase_hack(s, setup, NULL, test_compareAnimal_basic_greater_than_2);
    //tcase_hack(s, setup, NULL, test_compareAnimal_same_habitat1);
    //tcase_hack(s, setup, NULL, test_compareAnimal_same_habitat2);

    tcase_hack(s, setup, NULL, test_averageHungerScale_many_species);
    tcase_hack(s, setup, NULL, test_averageHungerScale_no_species);
    tcase_hack(s, setup, NULL, test_averageHungerScale_basic);

    tcase_hack(s, setup, NULL, test_sortAnimal_1);
    tcase_hack(s, setup, NULL, test_sortAnimal_2);
    tcase_hack(s, setup, NULL, test_sortAnimal_3);

    // Return Testing Suite
    return s;
}
