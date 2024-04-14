
DELIMITER //
DROP procedure IF EXISTS nostotapahtuma;
CREATE PROCEDURE nostotapahtuma(IN asiakas INT,IN tilin_numero INT, IN nosto DECIMAL(10,2))
BEGIN
    DECLARE tarkistettava_balance DECIMAL(10,2);

    SELECT balance INTO tarkistettava_balance 
    FROM account 
    WHERE idaccount = tilin_numero;

 IF EXISTS (SELECT * FROM customer_has_account WHERE idcustomer = asiakas AND idaccount = tilin_numero) THEN
        IF tarkistettava_balance IS NOT NULL AND tarkistettava_balance >0 AND tarkistettava_balance-nosto>=0 THEN
        UPDATE account 
        SET balance = balance - nosto 
        WHERE idaccount = tilin_numero;
        INSERT INTO withdrawal(idaccount, amount, timestamp) VALUES (tilin_numero, nosto, NOW());

        ELSEIF  tarkistettava_balance-nosto < 0 THEN
            SELECT 'You do not have enought money for that sum';

        ELSE
            SELECT 'You have no balance, U broke :)';

        END IF;
ELSE
    SELECT 'You do not have accest to that account';
END IF;

END//




CREATE PROCEDURE tilit_ja_kortit(IN asiakas INT)
BEGIN

    SELECT account.idaccount, account.balance, credit
    FROM customer
    JOIN customer_has_account ON customer.idcustomer = customer_has_account.idcustomer
    JOIN account ON customer_has_account.idaccount = account.idaccount
    WHERE asiakas = customer.idcustomer;

    SELECT idaccount, card.idcard, pin
    FROM card
    JOIN card_has_account ON card.idcard = card_has_account.idcard
    WHERE asiakas = idcustomer;

END//
DELIMITER ;
