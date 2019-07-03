public class Main {
    public static void main(String[] args) {
        BayesianNetwork bn = BayesianNetwork.buildAlarmExample();

        Sampling sampling = Sampling.buildAlarmExample(bn, 1000000);

        Probability probability = new Probability(sampling);
        probability.showBasicProbabilities();
        probability.showCalculateAnd("alarm","john");
        probability.showCalculateAnd("earthquake","john");
        probability.showCalculateAnd("john","lightning");
        probability.showCalculateConditional("john", "alarm");
        probability.showCalculateConditional("alarm", "earthquake");
        probability.showCalculateConditional("alarm", "robbery");
        probability.showCalculateConditional("john", "robbery");
        probability.showCalculateConditional("john", "alarm", "robbery");
    }
}
