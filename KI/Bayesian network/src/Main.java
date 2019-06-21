public class Main {
    public static void main(String[] args) {
        BayesianNetwork bn = BayesianNetwork.buildAlarmExample();

        Sampling sampling = Sampling.buildAlarmExample(bn, 1000000);

        Probability probability = new Probability(sampling);
        probability.showBasicProbabilities();
        probability.showCalculateAnd("alarm","john");
        probability.showCalculateConditional("john", "alarm");
        probability.showCalculateConditional("alarm", "earthquake");
        probability.showCalculateConditional("alarm", "robbery");
    }
}
