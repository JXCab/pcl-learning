/*
 * @Description: 
 * @Author: HCQ
 * @Company(School): UCAS
 * @Date: 2020-10-04 18:33:16
 * @LastEditors: HCQ
 * @LastEditTime: 2020-10-04 18:33:29
 */
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>

void PCDWrite(){
    std::cerr << " ========== PCDWrite ========== " << std::endl;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    // Fill in the cloud data
    cloud.width = 5;
    cloud.height = 2;
    cloud.is_dense = false;
    cloud.points.resize(cloud.width * cloud.height);

    for (auto &point : cloud)
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    pcl::io::savePCDFileASCII("pcd_write.pcd", cloud);
    std::cerr << "Saved " << cloud.size() << " data points to test_pcd.pcd." << std::endl;

    for (const auto &point : cloud)
        std::cerr << "    " << point.x << " " << point.y << " " << point.z << std::endl;
}

void FormatTransform(){
    std::cerr << " ========== PCD2TXT ========== " << std::endl;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../../../data/bunny.pcd", *cloud);

    std::ofstream outfile;
    outfile.open("bunny.txt");
    for(size_t i = 0; i < cloud->points.size(); ++i) {
        outfile << cloud->points[i].x << "\t" << cloud->points[i].y << "\t"  << cloud->points[i].z << "\n";
    }
    outfile.close();

    std::cerr << " ========== TXT2PCD ========== " << std::endl;
    std::ifstream infile;
    infile.open("bunny.txt");

    float x, y, z;
    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
    while (infile >> x >> y >> z) {
        cloud->push_back(pcl::PointXYZ(x, y, z));
    }
    pcl::io::savePCDFileBinary("bunny.pcd", *cloud);
    // pcl::io::savePCDFileASCII("bunny.pcd", *cloud);

    std::cerr << " ========== PCD2PLY ========== " << std::endl;
    pcl::io::savePLYFileBinary("bunny.ply", *cloud);

    /*
        其余：
        https://blog.csdn.net/taifyang/article/details/116382273?ops_request_misc=%257B%2522request

    */

}

int main(int argc, char **argv)
{
    PCDWrite();
    FormatTransform();

    return (0);
}
