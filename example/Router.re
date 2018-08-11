[@bs.get] external location: Dom.window => Dom.location = "";

[@bs.get] external pathname: Dom.location => string = "";

let currentPath = () =>
  switch ([%external window]) {
  | None => []
  | Some((window: Dom.window)) =>
    switch (window |> location |> pathname) {
    | ""
    | "/" => []
    | raw =>
      /* remove the preceeding /, which every pathname seems to have */
      let raw = Js.String.sliceToEnd(~from=1, raw);
      /* remove the trailing /, which some pathnames might have. Ugh */
      let raw =
        switch (Js.String.get(raw, Js.String.length(raw) - 1)) {
        | "/" => Js.String.slice(~from=0, ~to_=-1, raw)
        | _ => raw
        };
      raw |> Js.String.split("/") |> Array.to_list;
    }
  };

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
