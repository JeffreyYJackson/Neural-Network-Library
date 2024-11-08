model_(date)_(accuracy*1000)_(epoch time in seconds * 10)

# model_07.29.20.39.39_a892: 
16 Filters, MaxPool(2), 16 Filters, MaxPool(2), 4096->512->4
Dropout 0.3 each conv layer and first full layer
~2M Params

# model_07.29.21.09.48_a916:
Testing Bigger Conv Layer, want to see the GPU light up
128 Filters x 128 Filters x 32,768 fully connected layer input neurons
16,930,948 Parameters
Only made CPU go up
Miniscule increase in accuracy
Cuda wasn't available - same error from before "oserror: [winerror 126] the specified module could not be found"
Needed to add Desktop Development with C++ in Visual Studio Installer

# model_07.30.00.44.08_a858:
Set test set size to 200 (from 100, 800 total)
Need to randomly select test set
12.5s per epoch

# model_07.30.00.52.27_a847:
266,196 parameters:
Maxpool(4), 1024->256->4
11.5s per epoch
Maybe a bigger fully connected layer is needed?
What's the slow part? 1 second gain?!

# model_07.30.10.51.35_a877:
Removed Dropout Layers, no noticable difference
Add an epoch timer

# model_07.30.11.56.44_a842_t83
Randomly select images for eval & test set
Eval_loader was using the test set, now it's actually an evaluation, not much difference though?

# model_07.30.12.36.48_a861_t1898
Remove MaxPool(2) layer, fc: 16384->4096->4
67,132,116 Parameters
3 minute epoch!

# model_07.30.15.19.05_a916_t33
Tiny model: 8 Filters, MaxPool(4), fc: 1024->128->4
66,988 Parameters
Very good result! Go smaller!
Testing doing 100 epochs, 3 seconds each. 12-20 is undertraining. 25-30 is fine (89% acc), diminishing returns after that.

# model_07.30.15.24.43_a927_t27
1840 Parameters! 8 Filters, 2x MaxPool(4), 128->4
Less of a decrease in time, 2.6s vs. 3.3s
36484x smaller than the 67M param model! And better!

# model_07.30.15.28.17_a946_t14
520 Parameters! 4 Filters -> MaxPool(16) -> fc 64 -> 4

# model_07.30.15.34.28_a932_t14
372 Parameters! Just removed every layer I wasn't using
Lower accuracy is because of randomness, only last 5 epochs factor into avg_acc
