# Multilayer Perceptron

### Project goals

* Implementation of Multilayer Perceptron in matrix form (all layers are represented as weight matrices) (implemented by [ExpectoPatronus](https://github.com/ExpectoPatronus))
* Implementation of Multilayer Perceptron in graph form (each neuron is represented as some node object connected to other nodes by refs)
* Implementation of the GUI based on GTKMM4 (implemented by [ExpectoPatronus](https://github.com/ExpectoPatronus))

### Additional requirements

- The perceptron must:
  - classify images with handwritten letters of the Latin alphabet
  - have **from 2 to 5** hidden layers
  - use a sigmoid activation function for each hidden layer
  - be able to learn on an open dataset (e.g. EMNIST-letters presented in the datasets directory). The ratio of the test sample to the training one should be *no more than 2:8*, i.e. the test sample makes no more than 20% of the initial dataset
  - show accuracy on a test sample *over 70 percent*
  - be trained using the backpropagation method
- The interface of the program must provide the ability to:
  - run the experiment on the test sample or on a part of it, given by a floating point number between 0 and 1 (where 0 is the empty sample - the degenerate situation, and 1 is the whole test sample). After the experiment, there should be an average accuracy, precision, recall, f-measure and total time spent on the experiment displayed on the screen
  - load BMP images (image size can be up to 512x512) with Latin letters and classify them
  - draw two-color square images by hand in a separate window
  - start the real-time training process for a user-defined number of epochs with displaying the error control values for each training epoch. Make a report as a graph of the error change calculated on the test sample for each training epoch
  - run the training process using cross-validation for a given number of groups _k_
  - switch perceptron implementation (matrix or graph)
  - switch the number of perceptron hidden layers (from 2 to 5)
  - save to a file and load weights of perceptron from a file

### Additional materials
[Saved weights](./src/setting/)

[EMNIST train file](./src/datasets/emnist-letters-train.7z)

[EMNIST test file](./src/datasets/emnist-letters-test.7z)

[Latin letters images](./src/datasets/small_images/)