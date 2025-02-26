Network network;
    network.pushLayer(1);
    network.pushLayer(5, Linear);
    network.pushLayer(5, Linear);
    network.pushLayer(1, Linear);

    std::vector<std::vector<float>> trainingData = generateRandom2DVector(1000, 1);

    network.trainingData = trainingData;
    network.expectedValues = multiply2DVectorByTwo(trainingData);

    std::cout << "Initial cost: " << network.cost() << '\n';
    network.gradientDescent(.001, 1000);

    network.save("gradientDescentTest.txt");


    Network network = Network("gradientDescentTest.txt");

    if(!network.input({3.25})){return 0;}
    network.pass();
    network.printLayerVals(5);