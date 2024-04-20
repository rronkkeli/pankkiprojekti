-- MySQL Script generated by MySQL Workbench
-- Tue Mar 19 10:33:55 2024
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema bank
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema bank
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `bank` DEFAULT CHARACTER SET utf8 ;
USE `bank` ;

-- -----------------------------------------------------
-- Table `bank`.`customer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`customer` (
  `idcustomer` INT NOT NULL AUTO_INCREMENT,
  `fname` VARCHAR(45) NOT NULL,
  `lname` VARCHAR(45) NOT NULL,
  `phone_number` VARCHAR(20) NOT NULL,
  `birthdate` DATE NOT NULL,
  `address` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idcustomer`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`credentials`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`credentials` (
  `idcredentials` INT NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `idcustomer` INT NOT NULL,
  PRIMARY KEY (`idcredentials`, `idcustomer`),
  INDEX `fk_credentials_customer_idx` (`idcustomer` ASC) VISIBLE,
  CONSTRAINT `fk_credentials_customer`
    FOREIGN KEY (`idcustomer`)
    REFERENCES `bank`.`customer` (`idcustomer`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`card`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`card` (
  `idcard` VARCHAR(16) NOT NULL,
  `pin` VARCHAR(255) NOT NULL,
  `idcustomer` INT NOT NULL,
  PRIMARY KEY (`idcard`),
  INDEX `fk_card_customer1_idx` (`idcustomer` ASC) VISIBLE,
  CONSTRAINT `fk_card_customer1`
    FOREIGN KEY (`idcustomer`)
    REFERENCES `bank`.`customer` (`idcustomer`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`account` (
  `idaccount` INT NOT NULL AUTO_INCREMENT,
  `balance` DECIMAL(10,2) NOT NULL,
  `credit` DECIMAL(10,2) NULL,
  PRIMARY KEY (`idaccount`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`customer_has_account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`customer_has_account` (
  `idcustomer` INT NOT NULL,
  `idaccount` INT NOT NULL,
  PRIMARY KEY (`idcustomer`, `idaccount`),
  INDEX `fk_customer_has_account_account1_idx` (`idaccount` ASC) VISIBLE,
  INDEX `fk_customer_has_account_customer1_idx` (`idcustomer` ASC) VISIBLE,
  CONSTRAINT `fk_customer_has_account_customer1`
    FOREIGN KEY (`idcustomer`)
    REFERENCES `bank`.`customer` (`idcustomer`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_customer_has_account_account1`
    FOREIGN KEY (`idaccount`)
    REFERENCES `bank`.`account` (`idaccount`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`card_has_account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`card_has_account` (
  `idcard` VARCHAR(16) NOT NULL,
  `idaccount` INT NOT NULL,
  INDEX `fk_card_has_account_account1_idx` (`idaccount` ASC) VISIBLE,
  INDEX `fk_card_has_account_card1_idx` (`idcard` ASC) VISIBLE,
  CONSTRAINT `fk_card_has_account_card1`
    FOREIGN KEY (`idcard`)
    REFERENCES `bank`.`card` (`idcard`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_card_has_account_account1`
    FOREIGN KEY (`idaccount`)
    REFERENCES `bank`.`account` (`idaccount`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bank`.`withdrawal`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bank`.`withdrawal` (
  `idwithdrawal` INT NOT NULL AUTO_INCREMENT,
  `idaccount` INT NOT NULL,
  `amount` DECIMAL(10,2) NOT NULL,
  `timestamp` DATETIME NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`idwithdrawal`),
  INDEX `fk_transactions_account1_idx` (`idaccount` ASC) VISIBLE,
  CONSTRAINT `fk_transactions_account1`
    FOREIGN KEY (`idaccount`)
    REFERENCES `bank`.`account` (`idaccount`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Test value insertions on all tables
-- -----------------------------------------------------
INSERT INTO bank.customer VALUES (1, 'Aku', 'Ankka', '+302385022982', '1934-03-13', 'Paratiisitie 13, Ankkalinna');
INSERT INTO bank.customer VALUES (2, 'Iines', 'Ankka', '+1234567890', '1920-10-20', 'Helytie 6, Ankkalinna');
-- Pin 1234;
INSERT INTO bank.card VALUES ('06000622F0', '$2a$12$eoRO4an4QdEsUhbhwct52uNwqPFKFsLCim2GWpmaly3z77.H8xKAi', 1);
-- Pin 4321;
INSERT INTO bank.card VALUES ('06000DE540', '$2a$12$QnIME1de3u7kdAcMW1VVW.fiUAErV/WPSkTBGyEtEM1kzAV/yIKYG', 2);
INSERT INTO bank.account VALUES (1, 20.00, NULL);
INSERT INTO bank.account VALUES (2, 1923.71, 2000.00);
INSERT INTO bank.account VALUES (3, 480.00, 500.00);
INSERT INTO bank.card_has_account VALUES ('06000622F0', 1);
INSERT INTO bank.card_has_account VALUES ('06000DE540', 2);
INSERT INTO bank.card_has_account VALUES ('06000622F0', 3);
INSERT INTO bank.customer_has_account VALUES (1, 1);
INSERT INTO bank.customer_has_account VALUES (2, 2);
INSERT INTO bank.customer_has_account VALUES (1, 3);
INSERT INTO bank.withdrawal VALUES (1, 2, 50.00, '2022-11-06 10:31:11');
INSERT INTO bank.withdrawal VALUES (2, 1, 10.00, '2022-11-08 08:02:57');
INSERT INTO bank.withdrawal VALUES (3, 1, 5.00, '2022-11-14 07:55:21');
INSERT INTO bank.withdrawal VALUES (4, 2, 100.00, '2022-11-15 13:12:07');
INSERT INTO bank.withdrawal VALUES (5, 2, 80.00, '2022-11-17 19:22:03');
INSERT INTO bank.withdrawal VALUES (6, 3, 20.00, '2022-11-25 15:35:44');
-- Password 313131;
INSERT INTO bank.credentials VALUES (13031934, '$2a$12$HcRqgJFcRl4rZ.GrUb19CuEqxab/8Rha0zXUGhc/dpWobErOy1oXW', 1);
-- Password 999999;
INSERT INTO bank.credentials VALUES (20101920, '$2a$12$kaLD1nSl98hd5NP2jZm5FOLhbgIlrN7VW87mxM1T9TNVS9zeZQiT.', 2);

-- -----------------------------------------------------
-- Create test user for test database
-- -----------------------------------------------------
CREATE USER IF NOT EXISTS 'bankadmin'@'localhost' IDENTIFIED BY 'bankadminpassword';
GRANT ALL ON `bank`.* TO 'bankadmin'@'localhost';