# ZooDisaster

This program simulates an event in which a malfunction with a zoo's cage doors causes them to swing open and let the animals roam the zoo free. This allows some of the animals to eat each other. Specifically,

antelope eats grass
big-fish eats little-fish
bug eats bug 
bug eats leaves
bear eats big-fish
bear eats bug
bear eats chicken
bear eats cow
bear eats leaves
bear eats sheep
chicken eats bug
cow eats grass
fox eats chicken
fox eats sheep
giraffe eats leaves
lion eats antelope
lion eats cow
panda eats leaves
sheep eats grass

The rules of the simulation are simple. Assume some of these animals are lined up left-to-right. Start with the animal on the left. Animals always eat left to right (unless that animal is the left-most animal, in which it can only eat to the right). If the current animal we are concerned with cannot eat either to its left or right, move on to the next animal, and do the same for it. If the current animal can eat either, remove the animal it ate from the list, and start the process over from the beginning with the updated list. When we reach the last animal, if it cannot eat the animal to its left, the simulation is complete; no more eating will occur.

The goal of this program is, provided a lineup of animals, determine what the lineup looks like after the eating process has finished. The input should be a string ("animal1,animal2,...") of animals from the zoo, and the output should be a series of messages displaying the steps that were taken in the simulation. The first message should be the initial lineup string. The last message should be a new lineup string that displays what the old lineup looks like after the eating process. Each other message should describe, in order, which animals ate which during the simulation. For example, if the input is "fox,bug,chicken,grass,sheep", the output should be something like:

fox,bug,chicken,grass,sheep 
chicken eats bug 
fox eats chicken 
sheep eats grass 
fox eats sheep 
fox
