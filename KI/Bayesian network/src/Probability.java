import java.util.LinkedList;
import java.util.List;

public class Probability {
    private List<Sample> samples;
    private List<String> samplingOrder;
    private List<Double> probabilitiesAccordingToOrder;

    Probability(Sampling samples) {
        this.samples = samples.getSamples();
        samplingOrder = samples.getSamplingOrder();
        probabilitiesAccordingToOrder = new LinkedList<>();
        calculateBasicProbabilities();
    }

    public void showBasicProbabilities() {
        for (int i = 0; i < samplingOrder.size(); i++) {
            System.out.println(samplingOrder.get(i) + ": " + probabilitiesAccordingToOrder.get(i));
        }
    }

    private void calculateBasicProbabilities() {
        for (String node : samplingOrder) {
            probabilitiesAccordingToOrder.add(calculateProbabilityFromOrder(node));
        }
    }

    private double calculateProbabilityFromOrder(String name) {
        int position = samplingOrder.indexOf(name);
        double trueCount = 0.0;
        for (Sample sample : samples) {
            if (sample.getSigns()[position] == 't')
                trueCount++;
        }
        return trueCount / (double) samples.size();
    }

    public void showCalculateAnd(String first, String second) {
        System.out.print("probability of " + first + " and " + second + " is ");
        System.out.println(calculateAnd(first, second));
    }

    private double calculateAnd(String first, String second) {
        int positionF = samplingOrder.indexOf(first);
        int positionS = samplingOrder.indexOf(second);
        if (positionF == -1 || positionS == -1)
            throw new IllegalArgumentException("do not know one of given arguments");
        double trueCount = 0.0;
        for (Sample sample : samples) {
            if (sample.getSigns()[positionF] == 't' && sample.getSigns()[positionS] == 't')
                trueCount++;
        }
        return trueCount / (double) samples.size();
    }

    public void showCalculateConditional(String event, String condition) {
        System.out.print("probability of " + event + " under the condition " + condition + " is ");
        System.out.println(calculateConditional(event, condition));
    }

    private double calculateConditional(String event, String condition) {
        int positionE = samplingOrder.indexOf(event);
        int positionC = samplingOrder.indexOf(condition);
        if (positionE == -1 || positionC == -1)
            throw new IllegalArgumentException("do not know one of given arguments");
        double trueCount = 0.0;
        double conditionTrueCount = 0.0;
        for (Sample sample : samples) {
            if (sample.getSigns()[positionC] == 't') {
                conditionTrueCount++;
                if (sample.getSigns()[positionE] == 't')
                    trueCount++;
            }
        }
        return trueCount / conditionTrueCount;
    }

    public void showCalculateConditional(String target, String event, String condition) {
        System.out.print("probability of " + target + " under the condition " + event + " and " + condition + " is ");
        System.out.println(calculateConditional(target, event, condition));
    }

    private double calculateConditional(String event, String condition1, String condition2) {
        int positionE = samplingOrder.indexOf(event);
        int positionC1 = samplingOrder.indexOf(condition1);
        int positionC2 = samplingOrder.indexOf(condition2);
        if (positionE == -1 || positionC1 == -1 || positionC2 == -1)
            throw new IllegalArgumentException("do not know one of given arguments");
        double trueCount = 0.0;
        double conditionTrueCount = 0.0;
        for (Sample sample : samples) {
            if (sample.getSigns()[positionC1] == 't') {
                if(sample.getSigns()[positionC2] == 't') {
                    conditionTrueCount++;
                    if (sample.getSigns()[positionE] == 't')
                        trueCount++;
                }
            }
        }
        return trueCount / conditionTrueCount;
    }
}
