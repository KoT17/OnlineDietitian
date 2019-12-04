-- MySQL dump 10.13  Distrib 8.0.17, for Win64 (x86_64)
--
-- Host: localhost    Database: user_db
-- ------------------------------------------------------
-- Server version	8.0.17

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `username` varchar(50) NOT NULL,
  `password` varchar(50) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `first_name` varchar(50) NOT NULL,
  `last_name` varchar(50) NOT NULL,
  `weight` int(11) DEFAULT NULL,
  `height` varchar(20) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `BMI` float DEFAULT NULL,
  `diet_plan_id` int(11) DEFAULT NULL,
  `diet_restriction` int(11) DEFAULT NULL,
  `activity_level` varchar(50) DEFAULT NULL,
  `gender` varchar(50) DEFAULT NULL,
  `survey_time_taken` datetime DEFAULT NULL,
  PRIMARY KEY (`username`),
  UNIQUE KEY `unique_vals` (`username`,`email`),
  UNIQUE KEY `unique_email` (`email`),
  KEY `diet_plan_id` (`diet_plan_id`),
  CONSTRAINT `users_ibfk_1` FOREIGN KEY (`diet_plan_id`) REFERENCES `diet_plans` (`diet_plan_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES ('cosmonwanda@gmail.com','iwishforthistobedone','cosmonwanda@gmail.com','Timmy','Turner',120,'48',20,NULL,103,3,'Regular Exercise','Male',NULL),('jimm@gmail.com','gottablast','jimm@gmail.com','Jimbles','Nontrombo',123,'12',12,12,107,2,'Regular Exercise','Male',NULL),('krustykrabisunfair@gmail.com','imready','krustykrabisunfair@gmail.com','Spongebob','Squarepants',300,'36',33,NULL,102,1,'Regular Exercise','Male',NULL),('pogchamp@gmail.com','pleasesaveme','pogchamp@gmail.com','Sean','Szumlanski',150,'60',28,NULL,101,0,'Regular Exercise','Male',NULL),('thenorth@gmail.com','youknownothing','thenorth@gmail.com','John','Snow',175,'72',25,NULL,100,2,'Regular Exercise','Male',NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-12-03 23:20:30
