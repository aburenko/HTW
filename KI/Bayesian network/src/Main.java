public class Main {
    public static void main(String[] args) {
        BayesianNetwork bn = BayesianNetwork.buildAlarmExample();

        Sampling sampling = Sampling.buildAlarmExample(bn, 1000);

        Probability probability = new Probability(sampling);
        probability.showBasicProbabilities();
    }
}
