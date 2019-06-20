import java.util.*;

class Sampling {
    private int samplingNumber;
    private BayesianNetwork bn;
    private List<String> samplingOrder;
    private List<Sample> samples;

    private Sampling(BayesianNetwork bn, int samplingsNumber) {
        this.bn = bn;
        this.samplingNumber = samplingsNumber;
        samples = new LinkedList<>();
        samplingOrder = new LinkedList<>();
        this.doSampling();
    }

    public List<String> getSamplingOrder() {
        return samplingOrder;
    }

    private void doSampling() {
        int nodeNumber = bn.getNodeNumber();
        List<NodeProbability> npList = bn.getNodes();
        // make nodes order list
        for (NodeProbability np:
             npList) {
            samplingOrder.add(np.getName());
        }
        System.out.println(samplingOrder);
        // make [samplingNumber] of sampling
        for(int j=0; j < samplingNumber; j++) {
            // make signs for nodes and fill with 0
            char []signs = new char[nodeNumber];
            for (int i = 0; i < nodeNumber; i++) {
                signs[i] = '0';
            }
            // calculate signs for each node
            for (int i = 0; i < nodeNumber; i++) {
                double value = Math.random();
                // get node values
                NodeProbability nodeProbability = npList.get(i);
                ArrayList<String> distribution = nodeProbability.getDistribution();
                ArrayList<Double> distributionValues = nodeProbability.getDistributionValues();
                int dependenciesNumber = nodeProbability.getDependenciesNumber();
                // get values for node dependencies
                char[] dependenciesSigns = new char[dependenciesNumber];
                int counterDependency = 0;
                for (String dependency : nodeProbability.getDependencies()) {
                    int counterSampling = 0;
                    for (String sampling : samplingOrder) {
                        if(dependency.equals(sampling)) {
                            dependenciesSigns[counterDependency] = signs[counterSampling];
                            break;
                        }
                        counterSampling++;
                    }
                    counterDependency++;
                }
                // create distribution to search
                String searchedDistribution = "t" + new String(dependenciesSigns);
                // select distribution value
                int counter = 0;
                for (String d :
                        distribution) {
                    if(d.equals(searchedDistribution)) {
                        double trueRange = distributionValues.get(counter);
                        if (value < trueRange) {
                            signs[i] = 't';
                        } else {
                            signs[i] = 'f';
                        }
                        break;
                    }
                    counter++;
                }
            }
            samples.add(new Sample(signs));
        }
    }

    public static Sampling buildAlarmExample(BayesianNetwork bn, int samplingsNumber) {
        return new Sampling(bn, samplingsNumber);
    }

    public List<Sample> getSamples() {
        return samples;
    }

    public void showSamples() {
        System.out.println("Samples:");
        for (Sample sample:
                samples) {
            System.out.println("->" + Arrays.toString(sample.getSigns()));
        }
    }

}
