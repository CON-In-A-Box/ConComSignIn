<?php declare(strict_types=1);
/*.
    require_module 'standard';
.*/

namespace App\Modules\registration\Controller\Ticket;

use Slim\Http\Request;
use Slim\Http\Response;

class LostTicket extends BaseTicket
{


    public function buildResource(Request $request, Response $response, $params): array
    {
        $id = $params['id'];
        $aid = $this->getAccount($id, $request, $response, 'api.registration.ticket.lost');
        if (is_array($aid)) {
            return $aid;
        }

        $sql = "UPDATE `Registrations` SET `BadgesPickedUp` = `BadgesPickedUp` + 1  WHERE `RegistrationID` = $id AND `VoidDate` IS NULL;";
        $sth = $this->container->db->prepare($sql);
        $sth->execute();
        if ($sth->rowCount() == 0) {
            return [
            \App\Controller\BaseController::RESULT_TYPE,
            $this->errorResponse($request, $response, 'Conflict', 'Lost Ticket report Failed.', 409)];
        }

        $this->printBadge($request, $id);

        return [null];

    }


    /* end LostTicket */
}
