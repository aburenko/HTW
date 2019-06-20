import java.util.ArrayList;
import java.util.Arrays;

class NodeProbability {
    private String name;
    private ArrayList<String> dependencies = new ArrayList<>();
    private ArrayList<String> distribution = new ArrayList<>();
    private ArrayList<Double> distributionValues = new ArrayList<>();

    NodeProbability(String nodeName, String dependencies, String distribution) {
        this.name = nodeName;
        int dependenciesLength;
        if(!dependencies.isEmpty()) {
            String[] splitedDependencies = dependencies.split(" ");
            dependenciesLength = splitedDependencies.length;
            this.dependencies.addAll(Arrays.asList(splitedDependencies));
        } else {
            dependenciesLength = 0;
        }

        String[] splitedDistribution = distribution.split(" ");
        int distributionLength = splitedDistribution.length;

        // check if all possibilities are given
        if(distributionLength != Math.pow(2,dependenciesLength + 1))
            throw new IllegalArgumentException("not the right amount of distribution possibilities"
             + distributionLength + ":" + dependenciesLength);

        ArrayList<String> distributionPairs = new ArrayList<>(Arrays.asList(splitedDistribution));

        for (String paar:
             distributionPairs) {
            String[] paarArray = paar.split(":");
            String condition = paarArray[0];
            double value = Double.parseDouble(paarArray[1]);

            this.distribution.add(condition);
            this.distributionValues.add(value);
        }
    }

    public ArrayList<String> getDependencies() {
        return dependencies;
    }

    public int getDependenciesNumber() {
        return dependencies.size();
    }

    public ArrayList<String> getDistribution() {
        return distribution;
    }

    public ArrayList<Double> getDistributionValues() {
        return distributionValues;
    }

    public String getName() {
        return name;
    }
}
