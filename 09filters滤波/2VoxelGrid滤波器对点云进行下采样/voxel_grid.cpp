/*
 * @Description: 2VoxelGrid滤波器对点云进行下采样    https://www.cnblogs.com/li-yao7758258/p/6445831.html
 * @Author: HCQ
 * @Company(School): UCAS
 * @Email: 1756260160@qq.com
 * @Date: 2020-10-20 10:50:23
 * @LastEditTime: 2020-10-20 11:00:48
 * @FilePath: /pcl-learning/09filters滤波/2VoxelGrid滤波器对点云进行下采样/voxel_grid.cpp
 */
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>


/*
  每个体素内用体素中所有点的重心来近似显示体素中其他点，这样该体素内所有点都用一个重心点最终表示，
  对于所有体素处理后得到的过滤后的点云，这种方法比用体素中心逼近的方法更慢，但是对于采样点对应曲面的表示更为准确。
*/
int
main (int argc, char** argv)
{

  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());

  //点云对象的读取
  pcl::PCDReader reader;
 
  reader.read ("../table_scene_lms400.pcd", *cloud);    //读取点云到cloud中

  std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
       << " data points (" << pcl::getFieldsList (*cloud) << ")." << std::endl;

  /******************************************************************************
    创建一个voxel叶大小为1cm的pcl::VoxelGrid滤波器，
  **********************************************************************************/
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;  //创建滤波对象
  sor.setInputCloud (cloud);            //设置需要过滤的点云给滤波对象
  sor.setLeafSize (0.01f, 0.01f, 0.01f);  //设置滤波时创建的体素体积为1cm的立方体
  sor.filter (*cloud_filtered);           //执行滤波处理，存储输出

  std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
       << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";

  pcl::PCDWriter writer;
  writer.write ("../table_scene_lms400_downsampled.pcd", *cloud_filtered, 
         Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false);

  return (0);
}