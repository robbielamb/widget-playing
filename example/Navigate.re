let pathFor = (route) =>
  switch route {
  | Routes.AlertExampleRoute => "/alert"
  | Routes.BadgesExampleRoute => "/badges"
  | Routes.BreadcrumbExampleRoute => "/breadcrumbs"
  | Routes.ButtonExampleRoute => "/buttons"
  | Routes.CollapseExampleRoute => "/collapse"
  | Routes.DropdownExampleRoute => "/dropdown"
  | Routes.FormExampleRoute => "/forms"
  | Routes.ModalExampleRoute => "/modal"
  | Routes.PaginationExampleRoute => "/pagination"
  | Routes.ProgressExampleRoute => "/progress"
  | Routes.TableExampleRoute => "/tables"
  | Routes.TabExampleRoute => "/tabs"
  | Routes.NotFound => "/notFound"
  };

let _to = (route) => {
  let path = pathFor(route);
  ReasonReact.Router.push(path);
};
