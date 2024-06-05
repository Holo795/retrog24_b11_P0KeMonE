#include "model.h"

Model::Model() {
    data = new Data();
}

void Model::loadMap(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        int rows = in.readLine().toInt();
        int cols = in.readLine().toInt();
        map.resize(rows, std::vector<char>(cols));
        for (int i = 0; i < rows; ++i) {
            QString line = in.readLine();
            for (int j = 0; j < cols; ++j) {
                map[i][j] = line[j].toLatin1();
            }
        }
    }
}

const std::vector<std::vector<char>>& Model::getMap() const {
    return map;
}

Data * Model::getData() {
    return data;
}
