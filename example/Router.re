[@bs.get] external location : Dom.window => Dom.location = "";

[@bs.get] external pathname : Dom.location => string = "";

let pathHandler = (url: list(string)) =>
  Routes.(
    switch (url) {
    | ["alert"] => AlertExampleRoute
    | ["badges"] => BadgesExampleRoute
    | ["buttons"] => ButtonExampleRoute
    | ["breadcrumbs"] => BreadcrumbExampleRoute
    | ["collapse"] => CollapseExampleRoute
    | ["dropdown"] => DropdownExampleRoute
    | ["forms"] => FormExampleRoute
    | ["modal"] => ModalExampleRoute
    | ["pagination"] => PaginationExampleRoute
    | ["progress"] => ProgressExampleRoute
    | ["tables"] => TableExampleRoute
    | ["tabs"] => TabExampleRoute
    | _ => NotFound
    }
  );

let urlHandler = (url: ReasonReact.Router.url) => pathHandler(url.path);

let elementForRoute = route =>
  switch (route) {
  | Routes.AlertExampleRoute => <AlertExample message="This is an alert" />
  | Routes.BadgesExampleRoute => <BadgesExample />
  | Routes.BreadcrumbExampleRoute => <BreadcrumbExample />
  | Routes.ButtonExampleRoute => <ButtonExample />
  | Routes.CollapseExampleRoute => <CollapseExample />
  | Routes.DropdownExampleRoute => <DropdownExample />
  | Routes.FormExampleRoute => <FormsExample />
  | Routes.ModalExampleRoute => <ModalExample />
  | Routes.PaginationExampleRoute => <PaginationExample />
  | Routes.ProgressExampleRoute => <ProgressExample />
  | Routes.TableExampleRoute => <TableExample />
  | Routes.TabExampleRoute => <TabsExample />
  | Routes.NotFound => <div> (ReasonReact.string("Not Found")) </div>
  };