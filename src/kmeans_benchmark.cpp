#include <tbb/tbb.h>

#include <chrono>

#include "kmeans.h"
#include "kmeans_parallel.h"
#include "modules.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "missing argument: problem file" << std::endl;
  }
  std::ofstream out("benchmark.csv");

  std::vector<KMeansClusterDefinition> definitions(KMeansClusterDefinition::load(argv[1]));
  if (definitions.empty()) {
    std::printf("failed to open problem file %s\n", argv[1]);
    return -1;
  }

  DataSet training_set;
  training_set.generate_random(definitions);

  DataSet eval_set;
  eval_set.generate_random(definitions);

  // Points de départ pour initialiser l'algorithme
  std::vector<Point> start_points
      = start_points_random(training_set.m_points, (int)definitions.size(), 0);
  
  out << "x , y, elapsed_serial, elapsed_parallel, speedup, efficiency\n";

  int repeat = 10;
  double sum = 0.0;
  double efficience;
  
  for (int i = 0; i < repeat; i++) {
    double acceleration;
    double elapsed_serial_times;
    double elapsed_parallel_times;
    
    training_set.generate_random(definitions);
    eval_set.generate_random(definitions);
    
    out << training_set.m_points[i].x << ", " << training_set.m_points[i].y;
    
    for (const struct test_klass& item : algo) {
      std::cout << "BENCHMARK " << item.klass << "\n";
      std::shared_ptr<KMeans> kmeans = item.factory();

      double elapsed = 0.0;

      auto t1 = std::chrono::steady_clock::now();
      // Trouver les groupes dans le jeu de données
      kmeans->fit(training_set.m_points, start_points);
      auto t2 = std::chrono::steady_clock::now();
      elapsed += std::chrono::duration<double>(t2 - t1).count();
      std::cout << "fit: " << elapsed << std::endl;

      t1 = std::chrono::steady_clock::now();
      // classifier un nouveau jeu de données
      std::vector<uint8_t> eval_cluster;
      kmeans->classify(eval_set.m_points, eval_cluster);
      t2 = std::chrono::steady_clock::now();
      elapsed += std::chrono::duration<double>(t2 - t1).count();
      std::cout << "classify: " << elapsed << std::endl;

      t1 = std::chrono::steady_clock::now();

      // comparer pour obtenir le taux de précision
      std::unordered_map<size_t, size_t> mapping;
      make_cluster_mapping(kmeans->get_centers(), definitions, mapping);
      size_t good = kmeans->compare(eval_set.m_cluster, eval_cluster, mapping);

      t2 = std::chrono::steady_clock::now();
      elapsed += std::chrono::duration<double>(t2 - t1).count();
      std::cout << "compare: " << elapsed << ", precision: " << 100 * good / eval_cluster.size()
                << " %" << std::endl;

      item.klass == "serial" ? elapsed_serial_times = elapsed : elapsed_parallel_times = elapsed;
    }
    
    acceleration = elapsed_serial_times / elapsed_parallel_times;
    std::cout << "Acceleration ensemble " << i << ": " << acceleration << std::endl;
    
    out << ", " << elapsed_serial_times << ", " << elapsed_parallel_times;
    sum = sum + acceleration;
    efficience = acceleration / tbb::this_task_arena::max_concurrency();
    out << ", " << acceleration << ", " << efficience;
    out << std::endl;
  }

  double avg = sum / 10.0;
  std::cout << "Moyenne acceleration: " << avg << std::endl;

  return 0;
}
