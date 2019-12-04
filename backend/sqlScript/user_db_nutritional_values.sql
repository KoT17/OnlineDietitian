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
-- Table structure for table `nutritional_values`
--

DROP TABLE IF EXISTS `nutritional_values`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `nutritional_values` (
  `food_name` varchar(50) NOT NULL,
  `calories` varchar(50) DEFAULT NULL,
  `serving_size` varchar(50) NOT NULL,
  `total_fat` varchar(50) DEFAULT NULL,
  `cholesterol` varchar(50) DEFAULT NULL,
  `sodium` varchar(50) DEFAULT NULL,
  `carbohydrates` varchar(50) DEFAULT NULL,
  `sugars` varchar(50) DEFAULT NULL,
  `protein` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`food_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nutritional_values`
--

LOCK TABLES `nutritional_values` WRITE;
/*!40000 ALTER TABLE `nutritional_values` DISABLE KEYS */;
INSERT INTO `nutritional_values` VALUES ('Almond','45','2 Tbsp','1g','0mg','0mg','4g','1g','6g'),('Apple','95','1 Medium','.3g','0mg','2mg','25g','19g','.5g'),('Avocado','234','1 Cup','21g','0mg','10mg','12g','1g','2.9g'),('Bacon ','43','1 Strip','3.3g','9mg','137mg','.1g','0g','3g'),('Banana','105','1 Medium','.4g','0mg','1mg','27g','14g','1.3g'),('Basmati Rice','205','1 Cup','.4g','0mg','1.6mg','45g','.1g','4.3g'),('Biscuit','49','1 Small','2.3g','0mg','81mg','6g','.3g','1g'),('Black Beans','114','.5 Cup','.46g','50mg','1mg','20.39g','.28g','7.62g'),('Black-Eyed Peas','198','1 Cup','.9g','0mg','7mg','35g','6g','13g'),('Blueberries','84','1 Cup','.49g','0mg','1mg','21g','15g','1.1g'),('Broccoli','51','1 Stalk','.6g','0mg','50mg','10g','2.6g','4.3g'),('Brown Rice','216','1 Cup','1.8g','0mg','10mg','45g','.7g','5g'),('Brussel Sprouts','38','1 Cup','.3g','0mg','22mg','8g','1.9g','3g'),('Can of Tuna','110','1 Can','2.5g','35mg','320mg','0g','0g','20g'),('Cauliflower','146','1 Head Medium','1.6g','0mg','176mg','29g','11g','11g'),('Cereal (Corn Flakes) ','100','1 Cup','.1g','0mg','204mg','24g','2.7g','2.1g'),('Cheese ','106','1 Slice','7.8g','26mg','54mg','1.5g','.4g','7.5g'),('Chia Seeds','138','1 oz','9g','0mg','5mg','12g','0mg','4.7g'),('Chickpeas','46','1 Tbsp','.8g','0mg','3mg','8g','1.3g','2.4g'),('Coconut Yogurt Alternative','110','1 Cup','7g','15mg','45mg','10g','1g','1g'),('Corn','60','1/2 Cup ','.5g','0mg','260mg','11g','5g','2g'),('Cottage Cheese','222','1 Cup','10g','38mg','819mg','8g','6g','25g'),('Cucumber','8','1/2 Cucumber','0g','0mg','1mg','2g','0g','0g'),('Egg','15.8','1 Large Egg','.1g','0mg','54.8mg','.2g','.2g','3.6g'),('Fettuccine Alfredo','230','.66 cup','3.5g','15mg','700mg','44g','3g','8g'),('Gluten-Free Bread','80','1 Slice','1g','10mg','13mg','15g','1g','2g'),('Gluten-Free Oats','190','1/2 Cup ','4g','0mg','0mg','33g','0g','6g'),('Gravy','188','1 Cup','14g','5mg','1009mg','13g','1.9g','4.6g'),('Green Beans','30','1 Cup','.22g','0mg','6mg','6.27g','3.26g','1.83g'),('Green Bell Pepper','24','1 Medium','.2g','0mg','4mg','6g','2.9g','1g'),('Grilled Chicken','266','1 Cup Diced (140g)','10.4g','125mg','120mg','0g','0g','40.5g'),('Ground beef','218','3 Oz','13g','66.3mg','76mg','0g','0g','24g'),('Ham','203','1 Cup','8g','74mg','1684mg','2.1','0g','29g'),('Honey','120','1oz','9g','0mg','80mg','8g','4g','5g'),('Hummus','25','1 tbsp','1.4g','0mg','57mg','2.1g','0mg','1.2g'),('Lentil Balls','73.7','.05 Cup','2.3g','0mg','80.8mg','8.9g','.6g','5.2g'),('Lettuce','5','1 Cup Shredded','.1g','0mg','10mg','1g','.3g','.5g'),('Mashed Potatoes','214','1 Cup','7g','0mg','741mg','35g','1.2g','4g'),('Milk','103','1 Cup','2.4g','12mg','107mg','12g','13g','8g'),('Mushrooms','4','1 Medium','.1g','0mg','1mg','.6g','.4g','.6g'),('Mustard','3','1 Tsp','.2g','0mg','57mg','.3g','0g','.2g'),('Nutritional yeast','60','1/4 Cup','.5g','0mg','25mg','5g','0g','8g'),('Oatmeal','158','1 Cup','3.2g','0mg','115mg','27g','1.1g','6g'),('Onion','44','1 Medium','.1g','0mg','4mg','10g','4.7g','1.2g'),('Peanut Butter','190','2 Tablespoons','16g','0mg','5mg','6g','3g','8g'),('Pineapple','452','1 Fruit','1.1g','0mg','9mg','119g','89g','4.9g'),('Potato','110','1 Medium','0g','0mg','8mg','26g','1g','3g'),('Quinoa','222','1 Cup','6g','0mg','0mg','39g','1g','8g'),('Red Cabbage','261','1 Head Medium','1.3g','0mg','227mg','62g','32g','12g'),('Salad','18','3.1oz','.2g','0mg','10mg','3.7g','1.9g','.9g'),('Salami','41','1 Slice','3.2g','11mg','214mg','.3g','.1g','2.7g'),('Salmon','412','.5 Fillet','27g','109mg','117mg','0g','0g','40g'),('Sausage','286','1 Link','22.7g','129mg','1002mg','3.5g','.7g','16g'),('Spinach Wrap','270','1 Wrap','5g','0mg','630mg','47g','0g','8g'),('Steak','179','3 oz.','7.6g','89mg','48mg','0g','0g','26g'),('Sweet Peas','62','.5 Cup','.2g','0mg','58mg','11g','3.5g','4.1g'),('Sweet Potato','114','1 Cup Cubed','.1g','0mg','73mg','27g','6g','2.1g'),('Tempeh Bacon','151.5','50 Grams','9.9g','0mg','116.3mg','8.2g','3.3g','9.5g'),('Tofu','94','.5 Cup','6g','0mg','9mg','2.3g','0g','10g'),('Tomato','32','1 Cup Chopped','.3g','0mg','7.5mg','5.8g','3.9g','1.3g'),('Turkey','54','1 Oz','2.1g','31mg','29mg','0g','0g','8g'),('Walnut','523','1 Cup','52g','0mg','2mg','11g','2.1g','12g'),('White Bread','66.5','1 Slice','.9g','0mg','130mg','11.9g','1.4g','2.7g'),('White Rice','206','1 Cup','.4g','0mg','2mg','45g','.1g','4.3g'),('Whole Grain Fettuccine','210','2 oz','1g','0mg','0mg','41g','1g','9g'),('Whole Wheat Bread','69','1 Slice','.9g','0mg','112mg','12g','1.6g','3.6g');
/*!40000 ALTER TABLE `nutritional_values` ENABLE KEYS */;
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
