from sklearn.datasets import load_iris
from sklearn.tree import DecisionTreeClassifier, export_text, export_graphviz
import graphviz

# IRIS veri setini yükle
iris = load_iris()
X, y = iris.data, iris.target

# Karar ağacı modelini oluştur
model = DecisionTreeClassifier()
model.fit(X, y)

# Karar ağacını metin formatında görselleştir
tree_rules = export_text(model, feature_names=iris.feature_names)
print(tree_rules)

# Decision tree kurallarını bir metin dosyasına yazma
with open("decision_tree_rules.txt", "w") as file:
    file.write(tree_rules)

# Karar ağacını grafik formatında görselleştir
dot_data = export_graphviz(model, out_file=None, feature_names=iris.feature_names, class_names=iris.target_names, filled=True, rounded=True, special_characters=True)
graph = graphviz.Source(dot_data)
graph.render("iris_decision_tree", format="pdf")  # İstersen dosyaya da kaydedebilirsin

# Görselleştirmeyi görüntüle (opsiyonel)
graph.view("iris_decision_tree")
