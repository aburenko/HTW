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
}
